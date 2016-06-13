#include <sensor_controls.h>
#include <ui_sensor_controls.h>

sensor_controls::sensor_controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sensor_controls)
{
    ui->setupUi(this);
}

sensor_controls::~sensor_controls()
{
    delete ui;
}

void sensor_controls::on_edit()
{
    emit send_nav_packet();
}
