#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H

#include <QDialog>

namespace Ui {
class preferences_dialog;
}

class preferences_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit preferences_dialog(QWidget *parent = 0);
    ~preferences_dialog();
    Ui::preferences_dialog *ui;

public slots:

    void on_toggle_use_ip(bool);
    void on_config_files_btn();
    void on_edison_firmware_btn();
    void on_edison_logs_btn();

};

#endif // PREFERENCES_DIALOG_H
