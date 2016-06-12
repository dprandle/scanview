#ifndef NAVIGATION_CONTROLS_H
#define NAVIGATION_CONTROLS_H

#include <QWidget>

namespace Ui {
class sensor_controls;
}

class sensor_controls : public QWidget
{
    Q_OBJECT

public:
    explicit sensor_controls(QWidget *parent = 0);
    ~sensor_controls();
    Ui::sensor_controls *ui;

public slots:
    void on_edit();

signals:
    void send_nav_packet();

};

#endif // NAVIGATION_CONTROLS_H
