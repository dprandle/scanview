#include "scanview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScanView w;
    w.show();

    return a.exec();
}
