#include <include/console_view.h>
#include <ui_console_view.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

console_view::console_view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::console_view)
{
    ui->setupUi(this);
}

console_view::~console_view()
{
    delete ui;
}

void console_view::on_actionSave_triggered()
{
    QString fname = QFileDialog::getSaveFileName(this, "Save console to file", QString(), "*.txt");

    if (!fname.contains(".txt"))
        fname += ".txt";

    QFile file(fname);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << ui->m_echo_pt->toPlainText() << "\n";
    }
}

void console_view::on_actionClear_Screen_triggered()
{
    ui->m_echo_pt->clear();
}

void console_view::on_actionSelect_All_triggered()
{
    ui->m_echo_pt->selectAll();
}
