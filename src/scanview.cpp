#include <QTcpSocket>
#include <QTcpServer>
#include <QFileDialog>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QProgressDialog>
#include <QJsonDocument>
#include <QJsonObject>

#include <preferences_dialog.h>
#include <ui_sensor_controls.h>
#include <ui_preferences_dialog.h>
#include <scanview.h>
#include <ui_scanview.h>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>


#ifdef _WIN32
typedef int mode_t;
static const mode_t S_ISUID      = 0x08000000;           ///< does nothing
static const mode_t S_ISGID      = 0x04000000;           ///< does nothing
static const mode_t S_ISVTX      = 0x02000000;           ///< does nothing
static const mode_t S_IRUSR      = mode_t(_S_IREAD);     ///< read by user
static const mode_t S_IWUSR      = mode_t(_S_IWRITE);    ///< write by user
static const mode_t S_IXUSR      = 0x00400000;           ///< does nothing
#endif

edserver_packet_header::edserver_packet_header():
    data{0}
{

}

void edserver_packet_header::clear()
{
    for (int i = 0; i < HEADER_BYTE_SIZE; ++i)
        data[i] = 0;
}

ctrlmod_data::ctrlmod_data():
    m_read_buffer{0},
    m_read_cur_index(0),
    m_read_raw_index(0),
    m_cur_index(0),
    m_sckt(new QTcpSocket()),
    m_packets(),
    m_scan(),
    m_cur_plmsg(),
    m_cur_navmsg()
{
    m_scan.reserve(720);

    // Set up receive packets for ctrlmod
    m_packets.emplace(ScanView::hash_id(health_data_packet::Type()), new health_data_packet());
    m_packets.emplace(ScanView::hash_id(info_data_packet::Type()), new info_data_packet());
    m_packets.emplace(ScanView::hash_id(firmware_data_packet::Type()), new firmware_data_packet());
}

ctrlmod_data::~ctrlmod_data()
{
    delete m_sckt;
    while (m_packets.begin() != m_packets.end())
    {
        delete m_packets.begin()->second;
        m_packets.erase(m_packets.begin());
    }
}

edserver_data::edserver_data():
    m_read_buffer{0},
    m_read_cur_index(0),
    m_read_raw_index(0),
    m_cur_index(0),
    m_sckt(new QTcpSocket()),
    m_state(cs_idle),
    m_cur_header(),
    m_cur_data(),
    m_firmware_ack_amnt(0)
{}

edserver_data::~edserver_data()
{
    delete m_sckt;
}

ScanView::ScanView(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ScanView),
    m_preferences_dialog(new preferences_dialog(this)),
    m_ctrlm(),
    m_edserver(),
    m_scene(new QGraphicsScene),
    m_litem(nullptr),
    m_triangle(nullptr),
    m_firmware_progress(nullptr)
{
    m_ui->setupUi(this);

    // Set up the graphics stuff for the scan
    m_ui->m_mapview->setScene(m_scene);
    m_scene->setSceneRect(-7000,-7000,14000,14000);

    for (uint i = 0; i < 360; ++i)
    {
        QGraphicsEllipseItem * item = m_scene->addEllipse(0, 0, 40.0,40.0, QPen(), QBrush(Qt::SolidPattern));
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        item->setVisible(false);
    }

    QPolygonF tri;
    tri.append(QPointF(-80.0f,160.0f));
    tri.append(QPointF(0.0f,-160.0f));
    tri.append(QPointF(80.0f,160.0f));
    tri.append(QPointF(-80.0f,160.0f));
    m_triangle = m_scene->addPolygon(tri, QPen(Qt::red), QBrush(Qt::red, Qt::SolidPattern));
    m_triangle->setData(0, 13);

    QPen pen(Qt::blue);
    pen.setWidth(5);
    pen.setCosmetic(true);

    m_litem = m_scene->addLine(0,0,0,0,pen);
    m_litem->setData(0,15);

    connect(m_ctrlm.m_sckt, SIGNAL(readyRead()), this, SLOT(onCtrlmodDataAvailable()));
    connect(m_ctrlm.m_sckt, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onCtrlmodError(QAbstractSocket::SocketError)));
    connect(m_ctrlm.m_sckt, SIGNAL(connected()), this, SLOT(onCtrlmodConnected()));

    connect(m_edserver.m_sckt, SIGNAL(readyRead()), this, SLOT(onEdserverDataAvailable()));
    connect(m_edserver.m_sckt, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onEdserverError(QAbstractSocket::SocketError)));
    connect(m_edserver.m_sckt, SIGNAL(connected()), this, SLOT(onEdserverConnected()));

    connect(m_ui->sensors->ui->m_send_btn, SIGNAL(clicked()), this, SLOT(onCtrlmodSendCommand()));
    connect(m_ui->sensors, SIGNAL(send_nav_packet()), SLOT(onCtrlmodSendAltCommand()));

    connect(m_preferences_dialog->ui->btn_load_config, SIGNAL(clicked()), this, SLOT(on_actionLoadConfig_triggered()));
    connect(m_preferences_dialog->ui->btn_save_config, SIGNAL(clicked()), this, SLOT(on_actionSaveConfig_triggered()));

    QTimer *timer = new QTimer(this);
    QTimer *two_timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ctrlmodReadUpdate()));
    connect(two_timer, SIGNAL(timeout()), this, SLOT(edserverReadUpdate()));
    timer->start(10);
    two_timer->start(100);

    load_init_file();
}

ScanView::~ScanView()
{
    delete m_ui;
    delete m_scene;
}

void ScanView::closeEvent(QCloseEvent *event)
{
    save_init_file();
    event->accept();
}

void ScanView::on_actionLoadConfig_triggered()
{
    load_config_file();
}

void ScanView::on_actionSaveConfig_triggered()
{
    save_config_file();
}

void ScanView::on_actionClose_triggered()
{
    close();
}

void ScanView::on_actionAboutScanview_triggered()
{

}

void ScanView::load_init_file()
{
    QFile loadFile(STARTUP_SETTINGS);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        // just use program defaults if no startup file
        statusBar()->showMessage("No init file found - loading defaults...",3000);
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject load_object(loadDoc.object());
    loadFile.close();


    m_preferences_dialog->ui->le_host_name->setText(load_object.value("host_name").toString());
    m_preferences_dialog->ui->le_host_ip->setText(load_object.value("host_ip").toString());
    m_preferences_dialog->ui->le_password->setText(load_object.value("host_password").toString());
    m_preferences_dialog->ui->le_username->setText(load_object.value("host_username").toString());
    m_preferences_dialog->ui->sb_edserver_port->setValue(load_object.value("edison_server_port").toInt());
    m_preferences_dialog->ui->sb_port->setValue(load_object.value("ctrlmod_port").toInt());
    m_preferences_dialog->ui->gb_host_ip->setChecked(load_object.value("use_host_ip").toBool());

    m_preferences_dialog->ui->le_config_files->setText(load_object.value("config_file_dir").toString());
    m_preferences_dialog->ui->le_edison_firmware->setText(load_object.value("edison_firmware_dir").toString());
    m_preferences_dialog->ui->le_edison_log->setText(load_object.value("edison_log_dir").toString());
    statusBar()->showMessage("Successfully loaded init file " + QString(STARTUP_SETTINGS),5000);
}

void ScanView::save_init_file()
{
    QFile saveFile(STARTUP_SETTINGS);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    QJsonObject save_object;

    save_object["host_name"] = m_preferences_dialog->ui->le_host_name->text();
    save_object["host_ip"] = m_preferences_dialog->ui->le_host_ip->text();
    save_object["host_password"] = m_preferences_dialog->ui->le_password->text();
    save_object["host_username"] = m_preferences_dialog->ui->le_username->text();
    save_object["edison_server_port"] = m_preferences_dialog->ui->sb_edserver_port->value();
    save_object["ctrlmod_port"] = m_preferences_dialog->ui->sb_port->value();
    save_object["use_host_ip"] = m_preferences_dialog->ui->gb_host_ip->isChecked();

    save_object["config_file_dir"] = m_preferences_dialog->ui->le_config_files->text();
    save_object["edison_firmware_dir"] = m_preferences_dialog->ui->le_edison_firmware->text();
    save_object["edison_log_dir"] = m_preferences_dialog->ui->le_edison_log->text();

    QJsonDocument saveDoc(save_object);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}

void ScanView::load_config_file()
{
    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Select config file to load",
                                                 m_preferences_dialog->ui->le_config_files->text(),
                                                 "Config file (*.cfg)");
    if (fname.isEmpty())
        return;

    QFile loadFile(fname);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        statusBar()->showMessage("Could not load config file " + fname,5000);
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject load_object(loadDoc.object());
    loadFile.close();

    m_preferences_dialog->ui->le_host_name->setText(load_object.value("host_name").toString());
    m_preferences_dialog->ui->le_host_ip->setText(load_object.value("host_ip").toString());
    m_preferences_dialog->ui->le_password->setText(load_object.value("host_password").toString());
    m_preferences_dialog->ui->le_username->setText(load_object.value("host_username").toString());
    m_preferences_dialog->ui->sb_edserver_port->setValue(load_object.value("edison_server_port").toInt());
    m_preferences_dialog->ui->sb_port->setValue(load_object.value("ctrlmod_port").toInt());
    m_preferences_dialog->ui->gb_host_ip->setChecked(load_object.value("use_host_ip").toBool());
    statusBar()->showMessage("Successfully loaded config file " + fname,5000);
}

void ScanView::save_config_file()
{
    QString fname = QFileDialog::getSaveFileName(this,
                                                 "Save the config file",
                                                 m_preferences_dialog->ui->le_config_files->text(),
                                                 "Config file (*.cfg)");
    if (fname.isEmpty())
        return;

    int ind = fname.indexOf('.');
    if (ind != -1)
        fname.truncate(ind);

    fname += ".cfg";

    QFile saveFile(fname);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        statusBar()->showMessage("Could not save config file to " + fname,5000);
        return;
    }

    QJsonObject save_object;

    save_object["host_name"] = m_preferences_dialog->ui->le_host_name->text();
    save_object["host_ip"] = m_preferences_dialog->ui->le_host_ip->text();
    save_object["host_password"] = m_preferences_dialog->ui->le_password->text();
    save_object["host_username"] = m_preferences_dialog->ui->le_username->text();
    save_object["edison_server_port"] = m_preferences_dialog->ui->sb_edserver_port->value();
    save_object["ctrlmod_port"] = m_preferences_dialog->ui->sb_port->value();
    save_object["use_host_ip"] = m_preferences_dialog->ui->gb_host_ip->isChecked();

    QJsonDocument saveDoc(save_object);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
    statusBar()->showMessage("Successfully saved config file to " + fname,5000);
}

void ScanView::on_actionConnect_triggered()
{
    ctrlmod_connect();
    edserver_connect();
}

void ScanView::on_actionDisconnect_triggered()
{
    ctrlmod_disconnect();
    edserver_disconnect();
}

void ScanView::on_actionUpdateFirmware_triggered()
{
    m_firmware_progress = new QProgressDialog(this);
    m_firmware_progress->setLabelText("Uploading firmware...");
    m_firmware_progress->setCancelButton(nullptr);
    m_firmware_progress->setWindowTitle("Firmware Progress");

    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server - no connection active");
        return;
    }

    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Select ctrlmod update file",
                                                 m_preferences_dialog->ui->le_edison_firmware->text(),
                                                 "Firmware (ctrlmod*)");
    if (fname.isEmpty())
        return;

    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly))
    {
        cprint("Could not open file " + fname);
        return;
    }

    int i = fname.lastIndexOf('/');
    if (i < 0 || i >= fname.size())
    {
        cprint("Invalid file name for firmware... try again");
        return;
    }

    QString vers_name = fname.right(fname.size() - (i+1)); // strip the name

    QByteArray blob;
    blob.push_back(static_cast<char>(vers_name.size()));
    blob += vers_name;
    blob += file.readAll();
    edserver_packet_header header;
    header.hash_id = hash_id(UPDATE_FIRMWARE);
    header.data_size = blob.size();
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    m_edserver.m_sckt->write(blob.data(), header.data_size);
    m_firmware_progress->setMaximum(header.data_size);
    m_firmware_progress->setValue(0);
    cprint("Sent request to update firmware with " + fname);
}

void ScanView::on_actionStopCtrlmod_triggered()
{
    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server - no connection active");
        return;
    }

    edserver_packet_header header;
    header.hash_id = hash_id(KILL_CTRLMOD);
    header.data_size = 0;
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    cprint("Sent request to edison to set up auto-start - so ctrlmod and server will automatically start when edison boots up");
}

void ScanView::on_actionSetupAutostart_triggered()
{
    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server - no connection active");
        return;
    }

    edserver_packet_header header;
    header.hash_id = hash_id(SETUP_EDISON_STARTUP);
    header.data_size = 0;
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    cprint("Sent request to edison to set up auto-start - so ctrlmod and server will automatically start when edison boots up");
}

void ScanView::on_actionRestartCtrlmod_triggered()
{
    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server - no connection active");
        return;
    }

    cprint("Sent restart ctrlmod request");
    ctrlmod_disconnect();

    edserver_packet_header header;
    header.hash_id = hash_id(RESTART_CTRLMOD);
    header.data_size = sizeof(int16_t);
    int16_t port = static_cast<int16_t>(m_preferences_dialog->ui->sb_port->value());
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    m_edserver.m_sckt->write((char*)&port, header.data_size);
}

void ScanView::on_actionGetLog_triggered()
{
    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server- no connection active");
        return;
    }

    edserver_packet_header header;
    header.hash_id = hash_id(GET_LOG_FILES);
    header.data_size = 0;
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    cprint("Sent request to edison to get log files");
}

void ScanView::on_actionRemoveLogs_triggered()
{
    if (m_edserver.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to edison server - no connection active");
        return;
    }

    edserver_packet_header header;
    header.hash_id = hash_id(CLEAR_LOGS);
    header.data_size = 0;
    m_edserver.m_sckt->write((char*)header.data, HEADER_BYTE_SIZE);
    cprint("Sent request to edison to clear log files");
}

void ScanView::onCtrlmodError(QAbstractSocket::SocketError)
{
    cprint("Error trying to connect with ctrlmod " + m_ctrlm.m_sckt->errorString());
}

void ScanView::onCtrlmodConnected()
{
    if (m_ctrlm.m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Connected to ctrlmod on " + m_ctrlm.m_sckt->peerAddress().toString() + ":" + QString::number(m_ctrlm.m_sckt->peerPort()));
        m_ctrlm.m_sckt->setSocketOption(QAbstractSocket::LowDelayOption, QVariant());
    }
    else
        cprint("Could not connect to ctrlmod");
}

void ScanView::onCtrlmodSendCommand()
{
    if (m_ctrlm.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to ctrlmod - no connection active");
        return;
    }
    command_t com_to_send;
    rp_lidar_command_type cmd = static_cast<rp_lidar_command_type>(m_ui->sensors->ui->m_command_cbox->currentIndex());
    com_to_send.hash_id = hash_id("rplidar_request");
    com_to_send.cmd_data = cmd;
    m_ctrlm.m_sckt->write((char*)com_to_send.data, COMMAND_BYTE_SIZE);
}

void ScanView::ctrlmodReadUpdate()
{
    while (m_ctrlm.m_read_cur_index != m_ctrlm.m_read_raw_index)
    {
        ctrlmod_handle_byte(m_ctrlm.m_read_buffer[m_ctrlm.m_read_cur_index]);
        ++m_ctrlm.m_read_cur_index;
        if (m_ctrlm.m_read_cur_index == READ_BUF_SIZE)
            m_ctrlm.m_read_cur_index = 0;
    }
}

void ScanView::onCtrlmodSendAltCommand()
{
    if (m_ctrlm.m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command to ctrlmod - no connection active");
        return;
    }
    command_t com_to_send;
    com_to_send.hash_id = hash_id("nav_system_request");

    com_to_send.cmd_data_d = m_ui->sensors->ui->m_alt_P_sb->value();
    com_to_send.cmd_data_d2 = m_ui->sensors->ui->m_alt_I_sb->value();
    com_to_send.cmd_data_d3 = m_ui->sensors->ui->m_alt_D_sb->value();
    com_to_send.cmd_data_d4 = m_ui->sensors->ui->m_alt_ramp_sb->value();
    com_to_send.cmd_data_d5 = m_ui->sensors->ui->m_bias_x_sb->value();
    com_to_send.cmd_data_d6 = m_ui->sensors->ui->m_bias_y_sb->value();
    com_to_send.cmd_data_d7 = m_ui->sensors->ui->m_g_factor_sb->value();
    com_to_send.cmd_data_d8 = m_ui->sensors->ui->m_bias_threshold_sb->value();

    if (m_ui->sensors->ui->m_ant_reset_windup_cb->isChecked())
        com_to_send.cmd_data |= 0x10;
    if (m_ui->sensors->ui->m_complex_der_cb->isChecked())
        com_to_send.cmd_data |= 0x01;
    if (m_ui->sensors->ui->m_threshold_dropout_cb->isChecked())
        com_to_send.cmd_data |= 0x0100;

    m_ctrlm.m_sckt->write((char*)com_to_send.data, COMMAND_BYTE_SIZE);
}

void ScanView::onCtrlmodDataAvailable()
{
    QByteArray data = m_ctrlm.m_sckt->readAll();
    for (int i = 0; i < data.size(); ++i)
    {
        m_ctrlm.m_read_buffer[m_ctrlm.m_read_raw_index] = data[i];
        ++m_ctrlm.m_read_raw_index;
        if (m_ctrlm.m_read_raw_index == READ_BUF_SIZE)
            m_ctrlm.m_read_raw_index = 0;
        if (m_ctrlm.m_read_raw_index == m_ctrlm.m_read_cur_index)
            cprint("Error: Read buffer is overflowing");
    }
}


void ScanView::onEdserverDataAvailable()
{
    QByteArray data = m_edserver.m_sckt->readAll();
    for (int i = 0; i < data.size(); ++i)
    {
        m_edserver.m_read_buffer[m_edserver.m_read_raw_index] = data[i];
        ++m_edserver.m_read_raw_index;
        if (m_edserver.m_read_raw_index == READ_BUF_SIZE)
            m_edserver.m_read_raw_index = 0;
        if (m_edserver.m_read_raw_index == m_edserver.m_read_cur_index)
            cprint("Error: Read buffer is overflowing");
    }
}

void ScanView::onEdserverError(QAbstractSocket::SocketError)
{
    cprint("Error trying to connect with edison server: " + m_edserver.m_sckt->errorString());
}

void ScanView::onEdserverConnected()
{
    if (m_edserver.m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Connected to edison server on " + m_edserver.m_sckt->peerAddress().toString() + ":" + QString::number(m_edserver.m_sckt->peerPort()));
        m_edserver.m_sckt->setSocketOption(QAbstractSocket::LowDelayOption, QVariant());
    }
    else
        cprint("Could not connect to edison server");
}

void ScanView::edserverReadUpdate()
{
    while (m_edserver.m_read_cur_index != m_edserver.m_read_raw_index)
    {
        edserver_handle_byte(m_edserver.m_read_buffer[m_edserver.m_read_cur_index]);
        ++m_edserver.m_read_cur_index;
        if (m_edserver.m_read_cur_index == READ_BUF_SIZE)
            m_edserver.m_read_cur_index = 0;
    }
}

void ScanView::edserver_connect()
{
    QString host;
    if (m_preferences_dialog->ui->gb_host_ip->isChecked())
        host = m_preferences_dialog->ui->le_host_ip->text();
    else
        host = m_preferences_dialog->ui->le_host_name->text() + ".local";

    m_edserver.m_sckt->connectToHost(host, m_preferences_dialog->ui->sb_edserver_port->value());
}

void ScanView::edserver_disconnect()
{
    if (m_edserver.m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Closed connection with edison server on " + m_edserver.m_sckt->peerAddress().toString() + ":" + QString::number(m_edserver.m_sckt->peerPort()));
        m_edserver.m_sckt->disconnectFromHost();
    }
    else
    {
        cprint("No connection with edison server to close");
    }
}

uint ScanView::hash_id(const std::string & strng)
{
    uint hash = 5381;
    int c;
    const char * str = strng.c_str();
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void ScanView::edserver_handle_byte(char byte)
{
    if (m_edserver.m_state == cs_idle)
        m_edserver.m_state = cs_receiving_header;

    if (m_edserver.m_state == cs_receiving_header)
    {
        m_edserver.m_cur_header.data[m_edserver.m_cur_index] = byte;
        ++m_edserver.m_cur_index;
        if (m_edserver.m_cur_index == HEADER_BYTE_SIZE)
            edserver_received_header();
    }
    else
    {
        m_edserver.m_cur_data[m_edserver.m_cur_index] = byte;
        ++m_edserver.m_cur_index;
        if (m_edserver.m_cur_index == m_edserver.m_cur_data.size())
            edserver_received_all_data();
    }
}

void ScanView::edserver_received_header()
{
    if (m_edserver.m_cur_header.hash_id == hash_id(DATA_ACK))
    {
        m_edserver.m_firmware_ack_amnt = m_edserver.m_cur_header.data_size;
        if (m_firmware_progress != nullptr)
            m_firmware_progress->setValue(m_edserver.m_firmware_ack_amnt);
        m_edserver.m_cur_header.data_size = 0;
    }

    if (m_edserver.m_cur_header.data_size != 0)
    {
        m_edserver.m_state = cs_receiving_data;
        m_edserver.m_cur_data.resize(m_edserver.m_cur_header.data_size);
    }
    else
    {
        m_edserver.m_state = cs_idle;
        m_edserver.m_cur_header.clear();
    }
    m_edserver.m_cur_index = 0;
}

void ScanView::edserver_received_all_data()
{
    if (m_edserver.m_cur_header.hash_id == hash_id(COMMAND_ACK))
    {
        char * str = new char[m_edserver.m_cur_header.data_size];

        for (uint32_t i = 0; i < m_edserver.m_cur_header.data_size; ++i)
            str[i] = static_cast<char>(m_edserver.m_cur_data[i]);
        QString disp_str(str);
        disp_str.resize(m_edserver.m_cur_header.data_size);
        delete [] str;

        if (disp_str == QString(RESTART_CTRLMOD))
        {
            cprint("Received ack for command " + disp_str);
            QTimer::singleShot(1000, this, SLOT(ctrlmod_connect()));
        }
        else if (disp_str.contains("Successfully updated"))
        {
            m_firmware_progress->reset();
            delete m_firmware_progress;
            m_firmware_progress = nullptr;
            on_actionRestartCtrlmod_triggered();
        }
        else if (disp_str.contains(GET_FIRMWARE))
        {
            cprint("Firmware: " + disp_str.split(" ")[1]);
        }
        else
        {
            cprint("Received ack for command " + disp_str);
        }
    }

    if (m_edserver.m_cur_header.hash_id == hash_id(SERVER_CONSOLE_LOG) ||
            m_edserver.m_cur_header.hash_id == hash_id(SERVER_STATUS_LOG) ||
            m_edserver.m_cur_header.hash_id == hash_id(CONSOLE_LOG) ||
            m_edserver.m_cur_header.hash_id == hash_id(STATUS_LOG))
    {
        QString dir = m_preferences_dialog->ui->le_edison_log->text();

        if (!dir.isEmpty() && dir[dir.size()-1] != '/')
            dir += "/";

        QString nm;
        if(m_edserver.m_cur_header.hash_id == hash_id(SERVER_CONSOLE_LOG))
            nm = SERVER_CONSOLE_LOG;
        else if(m_edserver.m_cur_header.hash_id == hash_id(SERVER_STATUS_LOG))
            nm = SERVER_STATUS_LOG;
        else if(m_edserver.m_cur_header.hash_id == hash_id(CONSOLE_LOG))
            nm = CONSOLE_LOG;
        else if(m_edserver.m_cur_header.hash_id == hash_id(STATUS_LOG))
            nm = STATUS_LOG;

        QFile f(dir + nm);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return;

        QDataStream ds(&f);
        for (uint32_t i = 0; i < m_edserver.m_cur_data.size(); ++i)
            ds << m_edserver.m_cur_data[i];
        f.close();
    }

    m_edserver.m_cur_index = 0;
    m_edserver.m_state = cs_idle;
    m_edserver.m_cur_header.clear();
    m_edserver.m_cur_data.clear();
}

void ScanView::ctrlmod_connect()
{
    QString host;
    if (m_preferences_dialog->ui->gb_host_ip->isChecked())
        host = m_preferences_dialog->ui->le_host_ip->text();
    else
        host = m_preferences_dialog->ui->le_host_name->text() + ".local";

    m_ctrlm.m_sckt->connectToHost(host, m_preferences_dialog->ui->sb_port->value());
}

void ScanView::ctrlmod_disconnect()
{
    if (m_ctrlm.m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Closed connection with ctrlmod on " + m_ctrlm.m_sckt->peerAddress().toString() + ":" + QString::number(m_ctrlm.m_sckt->peerPort()));
        m_ctrlm.m_sckt->disconnectFromHost();
    }
    else
    {
        cprint("No connection with ctrlmod to close");
    }
}

void ScanView::ctrlmod_handle_byte(char byte)
{
    static hash_val curhash;
    static byte_4 pckt_size;
    static uint scanhashid = hash_id(complete_scan_data_packet::Type());
    static uint plmessage = hash_id(pulsed_light_message::Type());
    static uint navmessage = hash_id(nav_message::Type());

    if (m_ctrlm.m_cur_index < 4)
    {
        curhash.data[m_ctrlm.m_cur_index] = byte;
        ++m_ctrlm.m_cur_index;
    }
    else
    {
        std::unordered_map<uint,data_packet*>::iterator pcktIter = m_ctrlm.m_packets.find(curhash.hashval);
        if (pcktIter == m_ctrlm.m_packets.end())
        {

            if (curhash.hashval == scanhashid)
            {
                if (m_ctrlm.m_cur_index < 8)
                    pckt_size.data[m_ctrlm.m_cur_index-4] = byte;
                else
                {
                    uint b4index = (m_ctrlm.m_cur_index-8) / 4;
                    uint subi = (m_ctrlm.m_cur_index-8) % 4;

                    m_ctrlm.m_scan[b4index].data[subi] = byte;
                }

                ++m_ctrlm.m_cur_index;

                // If current index is 8 we have received first two unsigned ints..
                // First unsigned int is 4 byte hash val which determines packet
                // Second is 4 byte number indicating packet length
                if (m_ctrlm.m_cur_index == 8)
                    m_ctrlm.m_scan.resize(pckt_size.val); // I just reuse the "hashval" property as a size

                // scan is finished - mark it as such with current index etc
                if (m_ctrlm.m_cur_index == 8 + m_ctrlm.m_scan.size()*4)
                {
                    ctrlmod_scan_received();
                    m_ctrlm.m_cur_index = 0;
                    curhash.hashval = 0;
                    pckt_size.val = 0;
                }
                else if (m_ctrlm.m_cur_index > 8 + m_ctrlm.m_scan.size()*4)
                {
                    cprint("Received to much data for scan... error");
                }
            }
            else if (curhash.hashval == plmessage)
            {
                // Packet for pulsed light
                m_ctrlm.m_cur_plmsg.data[m_ctrlm.m_cur_index-4] = byte;
                ++m_ctrlm.m_cur_index;
                if (m_ctrlm.m_cur_index == 4 + m_ctrlm.m_cur_plmsg.size())
                {
                    ctrlmod_pl_received();
                    curhash.hashval = 0;
                    m_ctrlm.m_cur_index = 0;
                    pckt_size.val = 0;
                    m_ctrlm.m_cur_plmsg.zero();
                }
                else if (m_ctrlm.m_cur_index > 4 + m_ctrlm.m_cur_plmsg.size())
                {
                    cprint("Received to much data for plmessage... error");
                    m_ctrlm.m_cur_index = 0;
                    curhash.hashval = 0;
                    pckt_size.val = 0;
                    m_ctrlm.m_cur_plmsg.zero();
                }
            }
            else if (curhash.hashval == navmessage)
            {
                // Packet for pulsed lm_rp_dock->ui->m_rplidar_pt->setPlainTextight
                m_ctrlm.m_cur_navmsg.data[m_ctrlm.m_cur_index-4] = byte;
                ++m_ctrlm.m_cur_index;
                if (m_ctrlm.m_cur_index == 4 + m_ctrlm.m_cur_navmsg.size())
                {
                    ctrlmod_nav_received();
                    curhash.hashval = 0;
                    m_ctrlm.m_cur_index = 0;
                    pckt_size.val = 0;
                    m_ctrlm.m_cur_navmsg.zero();
                }
                else if (m_ctrlm.m_cur_index > 4 + m_ctrlm.m_cur_navmsg.size())
                {
                    cprint("Received to much data for nav message... error");
//                    curhash.hashval = 0;
//                    m_ctrlm.m_cur_index = 0;
//                    pckt_size.val = 0;
//                    m_ctrlm.m_cur_navmsg.zero();
                }
            }
            else
            {
                cprint("Incomplete packet - resetting indexes");
                curhash.hashval = 0;
                m_ctrlm.m_cur_index = 0;
                pckt_size.val = 0;
                m_ctrlm.m_cur_plmsg.zero();
                m_ctrlm.m_cur_navmsg.zero();
                m_ctrlm.m_scan.clear();
            }
        }
        else
        {
            // The received packet is one of the data packet types
            (*pcktIter->second)[m_ctrlm.m_cur_index-4] = byte;
            ++m_ctrlm.m_cur_index;
            if ( (m_ctrlm.m_cur_index-4) == pcktIter->second->size())
            {
                ctrlmod_pckt_received(pcktIter->second);
                curhash.hashval = 0;
                m_ctrlm.m_cur_index = 0;
                pckt_size.val = 0;
            }
        }
    }
}

void ScanView::ctrlmod_pckt_received(data_packet * pckt)
{
    if (pckt->type() != complete_scan_data_packet::Type())
    {
        cprint(QString(pckt->toString().c_str()));
    }

}

void ScanView::ctrlmod_scan_received()
{
    cprint("Received Scan: " + QString::number(m_ctrlm.m_scan.size()/2) + QString(" points"));
    if (m_ctrlm.m_scan.size() % 2 != 0)
    {
        cprint("Invalid Scan");
        return;
    }

    auto items = m_scene->items();
    auto itemIter = items.begin();

    uint count = 0;
    while (count < 360)
    {
        int dat = (*itemIter)->data(0).toInt();

        if (dat == 13 || dat == 15 || dat == 14)
            ++itemIter;

        if (count < m_ctrlm.m_scan.size()/2)
        {
            double angle = double(m_ctrlm.m_scan[count*2].val/64.0);
            double distance = double(m_ctrlm.m_scan[count*2+1].val/4.0);

            double unit_vec_x = cos(angle * PI / 180.0 - PI/2);
            double unit_vec_y = sin(angle * PI / 180.0 - PI/2);

            double xcoord = distance * unit_vec_x;
            double ycoord = distance * unit_vec_y;

            (*itemIter)->setPos(QPointF(xcoord,ycoord));
            (*itemIter)->setVisible(true);

        }
        else
        {
            (*itemIter)->setVisible(false);
        }
        ++itemIter;
        ++count;
    }
    m_litem->setPos(0,0);
    m_triangle->setPos(0,0);
}

void ScanView::ctrlmod_pl_received()
{
    m_ui->sensors->ui->m_ceiling_le->setText(QString::number(m_ctrlm.m_cur_plmsg.distance1 * 0.0328084) + " ft");
    m_ui->sensors->ui->m_floor_le->setText(QString::number(m_ctrlm.m_cur_plmsg.distance2 * 0.0328084) + " ft");
}

void ScanView::on_actionPreferences_triggered()
{
    if (m_preferences_dialog->exec() == QDialog::Accepted)
    {
        // do stuff
    }
}

void ScanView::ctrlmod_nav_received()
{
    m_litem->setLine(0, 0, m_ctrlm.m_cur_navmsg.rvec_corrected[0], -m_ctrlm.m_cur_navmsg.rvec_corrected[1]);
}

scan_data_packet::scan_data_packet()
{
    for (uint32_t i = 0; i < size(); ++i)
        data[i] = 0;
}

health_data_packet::health_data_packet()
{
    for (uint32_t i = 0; i < size(); ++i)
        data[i] = 0;
}

info_data_packet::info_data_packet()
{
    for (uint32_t i = 0; i < size(); ++i)
        data[i] = 0;
}

firmware_data_packet::firmware_data_packet()
{
    for (uint32_t i = 0; i < size(); ++i)
        data[i] = 0;
}

complete_scan_data_packet::complete_scan_data_packet()
{
    // do nothing
}

std::string complete_scan_data_packet::toString()
{
    std::string str;
    str.reserve(360*100);
    for (uint32_t i = 0; i < 360; ++i)
        str += data[i].toString();
    return str;
}

std::string scan_data_packet::toString()
{
    std::ostringstream ss;
    uint16_t angle = ((uint16_t)(angle6to0_C) >> 1) & 0x7F;
    angle |= ((uint32_t)(angle14to7) << 7) & 0x7F80;

    uint16_t distance = (uint16_t)(distance7to0) & 0xFF;
    distance |= ((uint32_t)(distance15to8) << 8) & 0xFF00;

    uint16_t ang = angle/64, dist = distance/4;
    ss << "\nAngle: " << ang;
    ss << "\nDistance: " << dist << "\n";
    return ss.str();
}

std::string health_data_packet::toString()
{
    std::ostringstream ss;
    ss << "Device Health\n";
    ss << "Status: ";
    if (status == 0x00)
            ss << "Good\n";
    else if (status == 0x01)
            ss << "Warning\n";
    else
            ss << "Error\n";

    int16_t error_code = (((int16_t)(error_code15to8)) << 8);
    error_code |= error_code7to0;

    ss << "Error Code: ";
    if (error_code == 0)
            ss << "None";
    else
            ss << error_code;

    return ss.str();
}

std::string info_data_packet::toString()
{
    std::ostringstream ss;
    ss << "Device Information\n";
    ss << "Model ID: " << int32_t(model) << "\n";
    ss << "Firware Version: " << int32_t(firmware_major) << "." << int32_t(firmware_minor) << "\n";
    ss << "Hardware Version: " << int32_t(hardware) << "\n";
    ss << "Serial Number: ";
    for (int32_t i = 15; i >= 0; --i)
        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int32_t>((uint8_t)(serialnumber[i]));
    return ss.str();
}

std::string firmware_data_packet::toString()
{
    std::string message = "Device Firmware\n";
    message.resize(size());
    for (uint32_t i = 0; i < size(); ++i)
            message[i] = (*this)[i];
    return message;
}
