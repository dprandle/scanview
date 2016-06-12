#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <QMainWindow>

namespace Ui {
class console_view;
}

class console_view : public QMainWindow
{
    Q_OBJECT

public:
    explicit console_view(QWidget *parent = 0);
    ~console_view();
    Ui::console_view *ui;

public slots:
    void on_actionSave_triggered();
    void on_actionClear_Screen_triggered();
    void on_actionSelect_All_triggered();

};

#endif // CONSOLE_VIEW_H
