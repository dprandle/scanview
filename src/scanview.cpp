#include <QTcpSocket>
#include <QTcpServer>
#include <QFileDialog>
#include <QGraphicsEllipseItem>
#include <QTimer>


#include <libssh/libssh.h>
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

ScanView::ScanView(QWidget *parent) :
    QMainWindow(parent),
    m_cur_index(0),
    m_ui(new Ui::ScanView),
    m_sckt(new QTcpSocket),
    m_scene(new QGraphicsScene),
    m_preferences_dialog(new preferences_dialog(this)),
    m_ssh_connected(false),
    m_scp_connected(false),
    m_scp_session(nullptr),
    my_ssh_session(nullptr)
{
    m_ui->setupUi(this);
    m_ui->m_mapview->setScene(m_scene);
    m_scene->setSceneRect(-7000,-7000,14000,14000);
    m_packets.emplace(_hash_id(health_data_packet::Type()), new health_data_packet());
    m_packets.emplace(_hash_id(info_data_packet::Type()), new info_data_packet());
    m_packets.emplace(_hash_id(firmware_data_packet::Type()), new firmware_data_packet());
    m_scan.reserve(720); // max points possible per scan

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

    connect(m_sckt, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    connect(m_sckt, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_sckt, SIGNAL(connected()), this, SLOT(onConnected()));

    connect(m_ui->sensors->ui->m_send_btn, SIGNAL(pressed()), this, SLOT(onSendCommand()));
    connect(m_ui->sensors, SIGNAL(send_nav_packet()), SLOT(onSendAltCommand()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readUpdate()));
    timer->start(10);
}

ScanView::~ScanView()
{
    delete m_sckt;
    delete m_ui;
    delete m_scene;
    while (m_packets.begin() != m_packets.end())
    {
        delete m_packets.begin()->second;
        m_packets.erase(m_packets.begin());
    }
}

void ScanView::on_actionConnect_triggered()
{
    QString host;
    if (m_preferences_dialog->ui->gb_host_ip->isChecked())
        host = m_preferences_dialog->ui->le_host_ip->text();
    else
        host = m_preferences_dialog->ui->le_host_name->text() + ".local";

    m_sckt->connectToHost(host, m_preferences_dialog->ui->sb_port->value());
}

void ScanView::_SSHDisconnect()
{
    if (m_ssh_connected)
    {
        cprint("Disconnected from edison");
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        m_ssh_connected = false;
    }
}

int ScanView::_verify_known_host()
{
  int state, hlen;
  unsigned char *hash = nullptr;
  char *hexa = nullptr;

  state = ssh_is_server_known(my_ssh_session);
  hlen = ssh_get_pubkey_hash(my_ssh_session, &hash);
  if (hlen < 0)
    return -1;
  switch (state)
  {
    case SSH_SERVER_KNOWN_OK:
      break; /* ok */
    case SSH_SERVER_KNOWN_CHANGED:
      cprint("Host key for server changed");
      delete hash;
      return -1;
    case SSH_SERVER_FOUND_OTHER:
      cprint("The host key for this server was not found but another type of key exists");
      delete hash;
      return -1;
    case SSH_SERVER_FILE_NOT_FOUND:
      cprint("Could not find known host file. If you accept the host key here, the file will be automatically created");
      /* fallback to SSH_SERVER_NOT_KNOWN behavior */
    case SSH_SERVER_NOT_KNOWN:
      hexa = ssh_get_hexa(hash, hlen);
      cprint("The server is unknown. Setting up...");
      delete hexa;
      if (ssh_write_knownhost(my_ssh_session) < 0)
      {
        cprint("SSH error writing known host - " + QString(strerror(errno)));
        delete hash;
        return -1;
      }
      break;
    case SSH_SERVER_ERROR:
      cprint("SSH Servor error - " + QString(ssh_get_error(my_ssh_session)));
      delete hash;
      return -1;
  }
  delete hash;
  return 0;
}

void ScanView::_SSHConnect()
{
    my_ssh_session = ssh_new();

    if (my_ssh_session == NULL)
        return;

    ssh_set_blocking(my_ssh_session, 1);

    QString host;
    if (m_preferences_dialog->ui->gb_host_ip->isChecked())
        host = m_preferences_dialog->ui->le_host_ip->text();
    else
        host = m_preferences_dialog->ui->le_host_name->text() + ".local";

    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host.toStdString().c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, m_preferences_dialog->ui->le_username->text().toStdString().c_str());

    // Connect to server
    int rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)
    {
        cprint("SSH Error - " + QString(ssh_get_error(my_ssh_session)) + " Have you connected to the edison AP?");
        ssh_free(my_ssh_session);
        return;
    }

    if (_verify_known_host() != 0)
    {
        cprint("Error verifying host");
        ssh_free(my_ssh_session);
        return;
    }

    // Authenticate ourselves
    while (ssh_userauth_password(my_ssh_session, nullptr, m_preferences_dialog->ui->le_password->text().toStdString().c_str()) != SSH_AUTH_SUCCESS);

    m_ssh_connected = true;
    cprint("Successfully logged in to edison");
}

void ScanView::on_actionDisconnect_triggered()
{
    if (m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Closed connection with " + m_sckt->peerAddress().toString() + ":" + QString::number(m_sckt->peerPort()));
        m_sckt->disconnectFromHost();
    }
    else
    {
        cprint("No connection to close");
    }
}

void ScanView::_SCPConnect(uint read_or_write)
{
    if (m_scp_connected)
    {
        cprint("Error - already have scp connection established");
        return;
    }

    if (!m_ssh_connected)
    {
        cprint("Error - must establish ssh connection before scp");
        return;
    }

    int rc;
    m_scp_session = ssh_scp_new(my_ssh_session, read_or_write | SSH_SCP_RECURSIVE, ".");
    if (m_scp_session == NULL)
    {
      cprint("Error allocating scp session: %s\n" + QString(ssh_get_error(my_ssh_session)));
      return;
    }
    rc = ssh_scp_init(m_scp_session);
    if (rc != SSH_OK)
    {
      cprint("Error initializing scp session: %s\n" + QString(ssh_get_error(my_ssh_session)));
      ssh_scp_free(m_scp_session);
      return;
    }
    m_scp_connected = true;
}

void ScanView::_SCPDisconnect()
{
    if (m_scp_connected)
    {
        cprint("Disconnected from scp session");
        ssh_scp_close(m_scp_session);
        ssh_scp_free(m_scp_session);
        m_scp_connected = false;
    }
}

void ScanView::_SSHCommand(const QString & cmd)
{
    if (!m_ssh_connected)
    {
        cprint("No ssh connection established with edison - cannot complete command " + cmd);
        return;
    }

    ssh_channel channel;
    char buffer[256];
    int rc;

    int nbytes = 0;
    channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL)
    {
        cprint("Error with creating ssh channel - " + QString(ssh_get_error(my_ssh_session)));
        return;
    }

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_channel_free(channel);
        cprint("Error with opening channel session - " + QString(ssh_get_error(my_ssh_session)));
        return;
    }


    while (ssh_channel_request_exec(channel, cmd.toStdString().c_str()) != SSH_OK);
    cprint("Successfully sent command " + cmd + " - waiting for reply...");

    QString txt = "";
    //usleep(10000);
    int max_iter = 0;
    while (ssh_channel_is_open(channel) && !ssh_channel_is_eof(channel) && max_iter < 20)
    {
      nbytes = ssh_channel_read_nonblocking(channel, buffer, sizeof(buffer), 0);
//      if (nbytes < 0)
//      {
//          ssh_channel_send_eof(channel);
//          ssh_channel_close(channel);
//          ssh_channel_free(channel);
//          cprint("Error with reading back command over channel - " + QString(ssh_get_error(my_ssh_session)));
//          return;
//      }
      if (nbytes > 0)
      {
          for (int i = 0; i < nbytes; ++i)
              txt.append(buffer[i]);
      }
      //usleep(1000);
      ++max_iter;
    }
    cprint(txt);
    cprint("Finished reading back reply");
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
}

void ScanView::on_actionUpdateFirmware_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Select ctrlmod update file",
                                                 m_preferences_dialog->ui->le_edison_firmware->text(),
                                                 "ctrlmod");
    if (fname.isEmpty())
        return;

    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly))
    {
        cprint("Could not open file " + fname);
        return;
    }
    QByteArray blob = file.readAll();

    cprint ("Attempting to update ctrmod service with " + fname);

    _SSHConnect();
    _SSHCommand("killall ctrlmod\n");
    _SCPConnect(SSH_SCP_WRITE);

    if (!m_scp_connected)
    {
        cprint("Cannot update ctrlmod service - scp service not connected");
        return;
    }

    int rc = ssh_scp_push_directory(m_scp_session, "progs", S_IRUSR | S_IWUSR | S_IXUSR);
    if (rc != SSH_OK)
    {
      cprint("Can't get in to remote directory: " + QString(ssh_get_error(my_ssh_session)));
      _SCPDisconnect();
      _SSHDisconnect();
      return;
    }
    cprint("Entering progs directory on remote host");

    rc = ssh_scp_push_file(m_scp_session, "ctrlmod", blob.size(), S_IRUSR |  S_IWUSR);
    if (rc != SSH_OK)
    {
      cprint("Can't open remote file: " + QString(ssh_get_error(my_ssh_session)));
      _SCPDisconnect();
      _SSHDisconnect();
      return;
    }
    cprint("Preparing ctrlmod file for writing..");

    rc = ssh_scp_write(m_scp_session, blob.data(), blob.size());
    if (rc != SSH_OK)
    {
      cprint("Can't write to remote file: " + QString(ssh_get_error(my_ssh_session)));
      return;
    }
    cprint("Successfully updated ctrmod service - restarting");
    _SSHCommand("progs/ctrlmod &\n");
    cprint("Successfully restarted ctrlmod service");
    _SCPDisconnect();
    _SSHDisconnect();
}

void ScanView::on_actionRestartCtrlmod_triggered()
{
    _SSHConnect();
    if (!m_ssh_connected)
        return;
    cprint("Attempting to restart ctrlmod service");
    _SSHCommand("killall ctrlmod");
    cprint("Stopped ctrlmod service");
    _SSHCommand("progs/ctrlmod &");
    cprint("Succfully restarted ctrlmod service");
    //_SSHDisconnect();
}

void ScanView::on_actionGetLog_triggered()
{
    _SSHConnect();
    _SCPConnect(SSH_SCP_READ);
    _SCPDisconnect();
    _SSHDisconnect();
}

void ScanView::on_actionRemoveLogs_triggered()
{
    _SSHConnect();
    _SCPConnect(SSH_SCP_WRITE);
    _SCPDisconnect();
    _SSHDisconnect();
}

void ScanView::onHostFound()
{
    cprint("Host found");
}

void ScanView::onError(QAbstractSocket::SocketError)
{
    cprint(m_sckt->errorString());
}

void ScanView::onConnected()
{
    if (m_sckt->state() == QAbstractSocket::ConnectedState)
    {
        cprint("Connected to " + m_sckt->peerAddress().toString() + ":" + QString::number(m_sckt->peerPort()));
        m_sckt->setSocketOption(QAbstractSocket::LowDelayOption, QVariant());
    }
    else
        cprint("Could not connect to host");

}

void ScanView::onSendCommand()
{
    if (m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command - no connection active");
        return;
    }
    command_t com_to_send;
    command_type cmd = static_cast<command_type>(m_ui->sensors->ui->m_command_cbox->currentIndex());
    com_to_send.hash_id = _hash_id("rplidar_request");
    com_to_send.cmd_data = cmd;
    m_sckt->write((char*)com_to_send.data, COMMAND_BYTE_SIZE);
    cprint("Sent rplidar command packet");
}

void ScanView::readUpdate()
{
    while (m_read_cur_index != m_read_raw_index)
    {
        _handle_byte(m_read_buffer[m_read_cur_index]);
        ++m_read_cur_index;
        if (m_read_cur_index == READ_BUF_SIZE)
            m_read_cur_index = 0;
    }
}

void ScanView::onSendAltCommand()
{
    if (m_sckt->state() != QAbstractSocket::ConnectedState)
    {
        cprint("Cannot send command - no connection active");
        return;
    }
    command_t com_to_send;
    com_to_send.hash_id = _hash_id("nav_system_request");

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

    m_sckt->write((char*)com_to_send.data, COMMAND_BYTE_SIZE);
}

uint ScanView::_hash_id(const std::string & strng)
{
    uint hash = 5381;
    int c;
    const char * str = strng.c_str();
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void ScanView::onDataAvailable()
{
    QByteArray data = m_sckt->readAll();
    for (int i = 0; i < data.size(); ++i)
    {
        m_read_buffer[m_read_raw_index] = data[i];
        ++m_read_raw_index;
        if (m_read_raw_index == READ_BUF_SIZE)
            m_read_raw_index = 0;
        if (m_read_raw_index == m_read_cur_index)
            cprint("Error: Read buffer is overflowing");
    }
}

void ScanView::_handle_byte(char byte)
{
    static hash_val curhash;
    static byte_4 pckt_size;
    static uint scanhashid = _hash_id(complete_scan_data_packet::Type());
    static uint plmessage = _hash_id(pulsed_light_message::Type());
    static uint navmessage = _hash_id(nav_message::Type());

    if (m_cur_index < 4)
    {
        curhash.data[m_cur_index] = byte;
        ++m_cur_index;
    }
    else
    {
        std::unordered_map<uint,data_packet*>::iterator pcktIter = m_packets.find(curhash.hashval);
        if (pcktIter == m_packets.end())
        {

            if (curhash.hashval == scanhashid)
            {
                if (m_cur_index < 8)
                    pckt_size.data[m_cur_index-4] = byte;
                else
                {
                    uint b4index = (m_cur_index-8) / 4;
                    uint subi = (m_cur_index-8) % 4;

                    m_scan[b4index].data[subi] = byte;
                }

                ++m_cur_index;

                // If current index is 8 we have received first two unsigned ints..
                // First unsigned int is 4 byte hash val which determines packet
                // Second is 4 byte number indicating packet length
                if (m_cur_index == 8)
                    m_scan.resize(pckt_size.val); // I just reuse the "hashval" property as a size

                // scan is finished - mark it as such with current index etc
                if ((m_cur_index-8) == m_scan.size()*4)
                {
                    _scan_received();
                    m_cur_index = 0;
                    curhash.hashval = 0;
                    pckt_size.val = 0;
                }
            }
            else if (curhash.hashval == plmessage)
            {
                // Packet for pulsed light
                m_cur_plmsg.data[m_cur_index-4] = byte;
                ++m_cur_index;
                if ((m_cur_index - 4) == m_cur_plmsg.size())
                {
                    _pl_received();
                    curhash.hashval = 0;
                    m_cur_index = 0;
                    pckt_size.val = 0;
                    m_cur_plmsg.zero();
                }
            }
            else if (curhash.hashval == navmessage)
            {
                // Packet for pulsed lm_rp_dock->ui->m_rplidar_pt->setPlainTextight
                m_cur_navmsg.data[m_cur_index-4] = byte;
                ++m_cur_index;
                if ((m_cur_index - 4) == m_cur_navmsg.size())
                {
                    _nav_received();
                    curhash.hashval = 0;
                    m_cur_index = 0;
                    pckt_size.val = 0;
                    m_cur_navmsg.zero();
                }
            }
            else
            {
                cprint("Missed packet");
                curhash.hashval = 0;
                m_cur_index = 0;
                pckt_size.val = 0;
            }
        }
        else
        {
            // The received packet is one of the data packet types
            (*pcktIter->second)[m_cur_index-4] = byte;
            ++m_cur_index;
            if ( (m_cur_index-4) == pcktIter->second->size())
            {
                _pckt_received(pcktIter->second);
                curhash.hashval = 0;
                m_cur_index = 0;
                pckt_size.val = 0;
            }
        }
    }
}

void ScanView::_pckt_received(data_packet * pckt)
{
    if (pckt->type() != complete_scan_data_packet::Type())
    {
        cprint(QString(pckt->toString().c_str()));
    }

}

void ScanView::_scan_received()
{
    cprint("Received Scan: " + QString::number(m_scan.size()/2) + QString(" points"));
    if (m_scan.size() % 2 != 0)
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

        if (count < m_scan.size()/2)
        {
            double angle = double(m_scan[count*2].val/64.0);
            double distance = double(m_scan[count*2+1].val/4.0);

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

void ScanView::_pl_received()
{
    m_ui->sensors->ui->m_ceiling_le->setText(QString::number(m_cur_plmsg.distance1 * 0.0328084) + " ft");
    m_ui->sensors->ui->m_floor_le->setText(QString::number(m_cur_plmsg.distance2 * 0.0328084) + " ft");
}

void ScanView::on_actionPreferences_triggered()
{
    if (m_preferences_dialog->exec() == QDialog::Accepted)
    {
        // do stuff
    }
}

void ScanView::_nav_received()
{
    m_litem->setLine(0, 0, m_cur_navmsg.rvec_corrected[0], -m_cur_navmsg.rvec_corrected[1]);
    cprint("Pitch: " + QString::number(m_cur_navmsg.pitch));
    cprint("Roll: " + QString::number(m_cur_navmsg.roll));
    cprint("Yaw: " + QString::number(m_cur_navmsg.yaw));
    cprint("Throttle: " + QString::number(m_cur_navmsg.throttle));
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
