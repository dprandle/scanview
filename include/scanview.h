#ifndef SCANVIEW_H
#define SCANVIEW_H

#include <QMainWindow>
#include <unordered_map>
#include <QAbstractSocket>
#include <libssh/libssh.h>
#include <ui_console_view.h>

#define cprint(str) m_ui->console->ui->m_echo_pt->appendPlainText(str)

#define PI 3.14159265359

#define READ_BUF_SIZE 20024
#define COMMAND_BYTE_SIZE 72

class data_packet;
class QTcpServer;
class QTcpSocket;
class QGraphicsScene;
class QGraphicsLineItem;
class QGraphicsItem;
class preferences_dialog;

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

union byte_4
{
    uint32_t val;
    char data[4];
};

struct vec3
{
    union
    {
        struct
        {
            double x;
            double y;
            double z;
        };
        char data[24];
    };
};

struct quat
{
    union
    {
        struct
        {
            double x;
            double y;
            double z;
            double w;
        };
        char data[32];
    };
};

struct command_t
{
    command_t():
        hash_id(0),
        cmd_data(0),
        cmd_data_d(0),
        cmd_data_d2(0),
        cmd_data_d3(0)
    {}

    union
    {
        struct
        {
            uint32_t hash_id;
            uint32_t cmd_data;
            double cmd_data_d;
            double cmd_data_d2;
            double cmd_data_d3;
            double cmd_data_d4;
            double cmd_data_d5;
            double cmd_data_d6;
            double cmd_data_d7;
            double cmd_data_d8;
        };
        uint8_t data[COMMAND_BYTE_SIZE];
    };

};

struct nav_message
{
    union
    {
        struct
        {
            int16_t throttle;
            int16_t pitch;
            int16_t roll;
            int16_t yaw;
            double rvec_raw[2];
            double rvec_corrected[2];
        };
        uint8_t data[40];
    };

    nav_message() {zero();}
    void zero()
    {
        for (uint i = 0; i < 40; ++i)
            data[i] = 0;
    }

    uint32_t size() {return 40;}
    std::string type() {return Type();}
    static std::string Type() {return "nav_message";}
};

struct pulsed_light_message
{
    union
    {
        struct
        {
            double distance1;
            double distance2;
            uint mraa_pin1;
            uint mraa_pin2;
            double pos1[3];
            double pos2[3];
            double orientation1[4];
            double orientation2[4];
        };
        char data[136];
    };

    pulsed_light_message() {zero();}
    void zero()
    {
        for (uint i = 0; i < 136; ++i)
            data[i] = 0;
    }
    uint size() {return 136;}

    std::string type() {return Type();}
    static std::string Type() {return "pulsed_light_message";}
};

class ScanView : public QMainWindow
{
    Q_OBJECT

public:
    enum command_type
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

    void on_actionPreferences_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionUpdateFirmware_triggered();
    void on_actionRestartCtrlmod_triggered();
    void on_actionGetLog_triggered();
    void on_actionRemoveLogs_triggered();

    void onDataAvailable();
    void onSendCommand();
    void readUpdate();

    void onHostFound();
    void onError(QAbstractSocket::SocketError);
    void onConnected();

    void onSendAltCommand();

private:

    void _SSHConnect();
    void _SSHDisconnect();

    void _SCPConnect(uint read_or_write);
    void _SCPDisconnect();

    void _SSHCommand(const QString & cmd);
    int _verify_known_host();

    bool m_ssh_connected;
    bool m_scp_connected;
    ssh_session my_ssh_session;
    ssh_scp m_scp_session;

    uint _hash_id(const std::string & str);
    void _pckt_received(data_packet * pckt);
    void _scan_received();
    void _pl_received();
    void _nav_received();
    void _handle_byte(char byte);

    char m_read_buffer[READ_BUF_SIZE];
    uint m_read_cur_index;
    uint m_read_raw_index;

    uint m_cur_index;

    Ui::ScanView *m_ui;
    QTcpSocket * m_sckt;
    preferences_dialog * m_preferences_dialog;
    QGraphicsScene * m_scene;
    std::unordered_map<uint, data_packet*> m_packets;
    std::vector<byte_4> m_scan;
    pulsed_light_message m_cur_plmsg;
    nav_message m_cur_navmsg;
    QGraphicsLineItem * m_litem;
    QGraphicsItem * m_triangle;
};

#endif // SCANVIEW_H
