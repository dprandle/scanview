#include <preferences_dialog.h>
#include <ui_preferences_dialog.h>
#include <QFileDialog>

preferences_dialog::preferences_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preferences_dialog)
{
    ui->setupUi(this);
}

preferences_dialog::~preferences_dialog()
{
    delete ui;
}

void preferences_dialog::on_toggle_use_ip(bool use)
{
    ui->le_host_name->setEnabled(!use);
}

void preferences_dialog::on_config_files_btn()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                                 "Select edison config files directory",
                                                      ui->le_config_files->text());
    ui->le_config_files->setText(dirname);
}

void preferences_dialog::on_edison_firmware_btn()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                                 "Select edison firware directory",
                                                      ui->le_edison_firmware->text());
    ui->le_edison_firmware->setText(dirname);
}

void preferences_dialog::on_edison_logs_btn()
{
    QString dirname = QFileDialog::getExistingDirectory(this,
                                                 "Select edison logs directory",
                                                      ui->le_edison_log->text());
    ui->le_edison_log->setText(dirname);
}
