#ifndef SCANVIEW_H
#define SCANVIEW_H

#include <QMainWindow>
#include <unordered_map>

#define PI 3.14159265359

class data_packet;
class QTcpServer;
class QTcpSocket;
class QGraphicsScene;

namespace Ui {
class ScanView;
}

typedef unsigned int uint;

struct hash_val
{
    union
    {
        uint hashval;
        char data[4];
    };
};

struct byte_4
{
    union
    {
        uint32_t val;
        char data[4];
    };
};

class ScanView : public QMainWindow
{
    Q_OBJECT

public:
    enum Command
    {
        HealthReq,
        InfoReq,
        StartScan,
        ForceScan,
        Stop,
        Reset
    };

    ScanView(QWidget *parent = 0);
    ~ScanView();

public slots:
    void onListen();
    void onStop();
    void onNewConnection();
    void onDataAvailable();
    void onSendCommand();

private:
    uint _hash_id(const std::string & str);
    void _pckt_received(data_packet * pckt);
    void _scan_received();

    uint m_cur_index;
    uint m_data_index;

    Ui::ScanView *m_ui;
    QTcpServer * m_server;
    QTcpSocket * m_sckt;
    QGraphicsScene * m_scene;
    std::unordered_map<uint, data_packet*> m_packets;
    std::vector<byte_4> m_scan;
};

#endif // SCANVIEW_H
