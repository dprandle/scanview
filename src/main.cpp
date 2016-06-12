#include "scanview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScanView * w = new ScanView;
    w->show();
    a.exec();
    delete w;
    return 0;
}
