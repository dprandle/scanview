#ifndef SCANVIEW_H
#define SCANVIEW_H

#include <QMainWindow>
#include <QAbstractSocket>


#include <libssh/libssh.h>
#include <unordered_map>
#include <ui_console_view.h>
#include <stdint.h>

#define cprint(str) m_ui->console->ui->m_echo_pt->appendPlainText(str)

#define PI 3.14159265359

#define READ_BUF_SIZE 20024
#define COMMAND_BYTE_SIZE 72


struct data_packet
{
    data_packet() {}
    virtual ~data_packet() {}
    virtual std::string toString()=0;
    virtual std::string type()=0;
    virtual uint32_t size()=0;
    virtual uint8_t & operator[](uint32_t index)=0;
    virtual uint8_t * dataptr()=0;
};

struct scan_data_packet : public data_packet
{
    scan_data_packet();

    virtual std::string toString();
    std::string type(){return Type();}
    virtual uint32_t size() {return Size();}
    virtual uint8_t & operator[](uint32_t index) {return data[index];}
    virtual uint8_t * dataptr(){return data;}
    static std::string Type() {return "scan";}
    static uint32_t Size() {return 5;}
    union
    {
        struct
        {
            uint8_t qual_s_sn;
            uint8_t angle6to0_C;
            uint8_t angle14to7;
            uint8_t distance7to0;
            uint8_t distance15to8;
        };

        uint8_t data[5];
    };
};

struct complete_scan_data_packet : public data_packet
{
    complete_scan_data_packet();

    virtual std::string toString();
    std::string type(){return Type();}
    virtual uint32_t size() {return Size();}
    virtual uint8_t & operator[](uint32_t index)
    {
        uint32_t data_ind = index % 5;
        uint32_t packet_ind = index / 5;
        return data[packet_ind][data_ind];
    }
    virtual uint8_t * dataptr(){return data[0].data;}
    static std::string Type() {return "complete_scan";}
    static uint32_t Size() {return 5 * 360;}
    scan_data_packet data[360];
};

struct health_data_packet : public data_packet
{
    health_data_packet();

    virtual std::string toString();
    virtual std::string type(){return Type();}
    virtual uint32_t size() {return Size();}
    virtual uint8_t & operator[](uint32_t index) {return data[index];}
    virtual uint8_t * dataptr(){return data;}
    static std::string Type() {return "health";}
    static uint32_t Size() {return 3;}
    union
    {
        struct
        {
            uint8_t status;
            uint8_t error_code7to0;
            uint8_t error_code15to8;
        };
        uint8_t data[3];
    };
};

struct info_data_packet : public data_packet
{

    info_data_packet();

    virtual std::string toString();
    virtual std::string type(){return Type();}
    virtual uint32_t size() {return Size();}
    virtual uint8_t & operator[](uint32_t index) {return data[index];}
    virtual uint8_t * dataptr(){return data;}
    static std::string Type() {return "info";}
    static uint32_t Size() {return 20;}
    union
    {
        struct
        {
            uint8_t model;
            uint8_t firmware_minor;
            uint8_t firmware_major;
            uint8_t hardware;
            uint8_t serialnumber[16];
        };
        uint8_t data[20];
    };
};

struct firmware_data_packet : public data_packet
{
    firmware_data_packet();
    virtual std::string toString();
    virtual std::string type(){return Type();}
    virtual uint32_t size() {return Size();}
    virtual uint8_t & operator[](uint32_t index) {return data[index];}
    virtual uint8_t * dataptr(){return data;}
    static std::string Type() {return "firmware";}
    static uint32_t Size() {return 56;}
    union
    {
        struct
        {
            uint8_t line1[18];
            uint8_t line2[29];
            uint8_t line3[9];
        };
        uint8_t data[56];
    };
};


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
