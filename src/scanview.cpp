
#include <QTcpSocket>
#include <scanview.h>
#include <ui_scanview.h>
#include <QTcpServer>
#include <iostream>
#include <edrplidar_packets.h>
#include <QGraphicsEllipseItem>
#include <sstream>

ScanView::ScanView(QWidget *parent) :
    QMainWindow(parent),
    m_cur_index(0),
    m_data_index(0),
    m_ui(new Ui::ScanView),
    m_server(new QTcpServer(this)),
    m_sckt(NULL),
    m_scene(new QGraphicsScene())
{
    m_ui->setupUi(this);
    m_ui->m_address_le->setText("172.20.203.149");
    m_ui->m_mapview->setScene(m_scene);
    m_scene->setSceneRect(-7000,-7000,14000,14000);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    m_packets.emplace(_hash_id(health_data_packet::Type()), new health_data_packet());
    m_packets.emplace(_hash_id(info_data_packet::Type()), new info_data_packet());
    m_packets.emplace(_hash_id(firmware_data_packet::Type()), new firmware_data_packet());
    m_scan.reserve(360); // max points possible per scan
}

ScanView::~ScanView()
{
    delete m_server;
    delete m_ui;
    delete m_scene;
    while (m_packets.begin() != m_packets.end())
    {
        delete m_packets.begin()->second;
        m_packets.erase(m_packets.begin());
    }
}

void ScanView::onListen()
{
    QHostAddress add;
    add.setAddress(m_ui->m_address_le->text());
    bool result = m_server->listen(add, m_ui->m_port_sb->value());
    if (result)
        m_ui->m_echo_pt->appendPlainText("Listening on " + m_server->serverAddress().toString() + ":" + QString::number(m_server->serverPort()));
    else
        m_ui->m_echo_pt->appendPlainText("Could not create a server");
}

void ScanView::onStop()
{
    if (m_sckt != NULL)
    {
        m_ui->m_command_cbox->setCurrentIndex(Stop);
        onSendCommand();
        m_sckt->close();
    }
    if (m_server->isListening())
        m_server->close();
    m_ui->m_echo_pt->appendPlainText("Closed port");
}

void ScanView::onSendCommand()
{
    uint hashid = _hash_id("rplidar_request");
    Command cmd = static_cast<Command>(m_ui->m_command_cbox->currentIndex());
    if (m_sckt == NULL)
    {
        m_ui->m_echo_pt->appendPlainText("Cannot send command - no devices connected");
        return;
    }
    m_sckt->write((char*)&hashid, sizeof(uint));
    m_sckt->write((char*)&cmd, sizeof(Command));
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

void ScanView::onNewConnection()
{
    m_sckt = m_server->nextPendingConnection();
    if (m_sckt == NULL)
    {
        m_ui->m_echo_pt->appendPlainText("Invalid Socket");
        return;
    }

    m_ui->m_echo_pt->appendPlainText("Connection from " + m_sckt->peerAddress().toString() + " with name " + m_sckt->peerName());
    connect(m_sckt, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
}

void ScanView::onDataAvailable()
{
    static hash_val curhash;
    static byte_4 pckt_size;

    QByteArray data = m_sckt->readAll();

    for (int i = 0; i < data.size(); ++i)
    {
        if (m_cur_index < 4)
        {
            curhash.data[m_cur_index] = data[m_cur_index];
        }
        else
        {
            std::unordered_map<uint,data_packet*>::iterator pcktIter = m_packets.find(curhash.hashval);
            if (pcktIter == m_packets.end())
            {
                if (curhash.hashval == _hash_id(complete_scan_data_packet::Type()))
                {
                    if (m_cur_index < 8)
                        pckt_size.data[m_cur_index-4] = data[i];
                    else
                    {
                        uint b4index = (m_cur_index-8) / 4;
                        uint subi = (m_cur_index-8) % 4;

                        m_scan[b4index].data[subi] = data[i];
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
                        m_cur_index = 0;
                        curhash.hashval = 0;
                        pckt_size.val = 0;
                        _scan_received();
                        m_scan.clear();
                    }
                }
                else
                {
                    m_ui->m_echo_pt->appendPlainText("Received packet with unknown hash val");
                    curhash.hashval = 0;
                    m_cur_index = 0;
                    pckt_size.val = 0;
                }
                continue;
            }
            (*pcktIter->second)[m_cur_index-4] = data[i];
            if ( (m_cur_index-3) == pcktIter->second->size())
            {
                _pckt_received(pcktIter->second);
                curhash.hashval = 0;
                m_cur_index = 0;
                pckt_size.val = 0;
                return;
            }
        }
        ++m_cur_index;
    }
}

void ScanView::_pckt_received(data_packet * pckt)
{
    if (pckt->type() != complete_scan_data_packet::Type())
        m_ui->m_echo_pt->setPlainText(QString(pckt->toString().c_str()));

}

void ScanView::_scan_received()
{
    m_scene->clear();
    m_ui->m_echo_pt->setPlainText("Received Scan: " + QString::number(m_scan.size()/2) + QString(" points"));


    if (m_scan.size() % 2 != 0)
    {
        m_ui->m_echo_pt->setPlainText("Invalid Scan");
        return;
    }
    for (uint i = 0; i < m_scan.size()/2; ++i)
    {
        double angle = double(m_scan[i*2].val/64.0);
        double distance = double(m_scan[i*2+1].val/4.0);

        double xcoord = distance * cos(angle * PI / 180.0 + PI/2);
        double ycoord = distance * sin(angle * PI / 180.0 + PI/2);
        QGraphicsEllipseItem * item = m_scene->addEllipse(xcoord, ycoord, 40.0,40.0, QPen(), QBrush(Qt::SolidPattern));
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
    QPolygonF tri;
    tri.append(QPointF(-80.0f,160.0f));
    tri.append(QPointF(0.0f,-160.0f));
    tri.append(QPointF(80.0f,160.0f));
    tri.append(QPointF(-80.0f,160.0f));
    m_scene->addPolygon(tri, QPen(Qt::red), QBrush(Qt::red, Qt::SolidPattern));
    //m_ui->m_scene_gv->fitInView(m_scene->sceneRect());
}
