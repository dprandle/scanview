/********************************************************************************
** Form generated from reading UI file 'console_view.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLE_VIEW_H
#define UI_CONSOLE_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_console_view
{
public:
    QAction *actionClear_Screen;
    QAction *actionSelect_All;
    QAction *actionSave;
    QWidget *console;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *m_echo_pt;
    QToolBar *toolBar;

    void setupUi(QMainWindow *console_view)
    {
        if (console_view->objectName().isEmpty())
            console_view->setObjectName(QStringLiteral("console_view"));
        console_view->resize(565, 217);
        actionClear_Screen = new QAction(console_view);
        actionClear_Screen->setObjectName(QStringLiteral("actionClear_Screen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/toolbars/icons/toolbars/clear_screen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_Screen->setIcon(icon);
        actionSelect_All = new QAction(console_view);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/toolbars/icons/toolbars/select_all.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_All->setIcon(icon1);
        actionSave = new QAction(console_view);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/toolbars/icons/toolbars/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        console = new QWidget(console_view);
        console->setObjectName(QStringLiteral("console"));
        verticalLayout = new QVBoxLayout(console);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_echo_pt = new QPlainTextEdit(console);
        m_echo_pt->setObjectName(QStringLiteral("m_echo_pt"));
        m_echo_pt->setReadOnly(true);

        verticalLayout->addWidget(m_echo_pt);

        console_view->setCentralWidget(console);
        toolBar = new QToolBar(console_view);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(16, 16));
        console_view->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionClear_Screen);
        toolBar->addAction(actionSelect_All);
        toolBar->addAction(actionSave);

        retranslateUi(console_view);

        QMetaObject::connectSlotsByName(console_view);
    } // setupUi

    void retranslateUi(QMainWindow *console_view)
    {
        console_view->setWindowTitle(QApplication::translate("console_view", "MainWindow", 0));
        actionClear_Screen->setText(QApplication::translate("console_view", "Clear Screen", 0));
#ifndef QT_NO_TOOLTIP
        actionClear_Screen->setToolTip(QApplication::translate("console_view", "Clear the console screen", 0));
#endif // QT_NO_TOOLTIP
        actionSelect_All->setText(QApplication::translate("console_view", "Select All", 0));
#ifndef QT_NO_TOOLTIP
        actionSelect_All->setToolTip(QApplication::translate("console_view", "Select all of the text", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("console_view", "Save", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("console_view", "Save console output to text file", 0));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("console_view", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class console_view: public Ui_console_view {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_VIEW_H
