/********************************************************************************
** Form generated from reading UI file 'scanview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANVIEW_H
#define UI_SCANVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <console_view.h>
#include <mapview.h>
#include <sensor_controls.h>

QT_BEGIN_NAMESPACE

class Ui_ScanView
{
public:
    QAction *actionClose;
    QAction *actionPreferences;
    QAction *actionSave_Configuration;
    QAction *actionClose_2;
    QAction *actionNew_Configuration;
    QAction *actionAbout_Scanview;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionUpdateFirmware;
    QAction *actionRestartCtrlmod;
    QAction *actionGetLog;
    QAction *actionRemoveLogs;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    MapView *m_mapview;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *m_sensor_dock;
    sensor_controls *sensors;
    QDockWidget *console_dock;
    console_view *console;

    void setupUi(QMainWindow *ScanView)
    {
        if (ScanView->objectName().isEmpty())
            ScanView->setObjectName(QStringLiteral("ScanView"));
        ScanView->resize(1186, 679);
        actionClose = new QAction(ScanView);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionPreferences = new QAction(ScanView);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionSave_Configuration = new QAction(ScanView);
        actionSave_Configuration->setObjectName(QStringLiteral("actionSave_Configuration"));
        actionClose_2 = new QAction(ScanView);
        actionClose_2->setObjectName(QStringLiteral("actionClose_2"));
        actionNew_Configuration = new QAction(ScanView);
        actionNew_Configuration->setObjectName(QStringLiteral("actionNew_Configuration"));
        actionAbout_Scanview = new QAction(ScanView);
        actionAbout_Scanview->setObjectName(QStringLiteral("actionAbout_Scanview"));
        actionConnect = new QAction(ScanView);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/toolbars/icons/toolbars/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(ScanView);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/toolbars/icons/toolbars/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionUpdateFirmware = new QAction(ScanView);
        actionUpdateFirmware->setObjectName(QStringLiteral("actionUpdateFirmware"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/toolbars/icons/toolbars/update_firmware.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdateFirmware->setIcon(icon2);
        actionRestartCtrlmod = new QAction(ScanView);
        actionRestartCtrlmod->setObjectName(QStringLiteral("actionRestartCtrlmod"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/toolbars/icons/toolbars/restart_edison.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestartCtrlmod->setIcon(icon3);
        actionGetLog = new QAction(ScanView);
        actionGetLog->setObjectName(QStringLiteral("actionGetLog"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/toolbars/icons/toolbars/get_log_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGetLog->setIcon(icon4);
        actionRemoveLogs = new QAction(ScanView);
        actionRemoveLogs->setObjectName(QStringLiteral("actionRemoveLogs"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/toolbars/icons/toolbars/delete_logs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemoveLogs->setIcon(icon5);
        centralWidget = new QWidget(ScanView);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_mapview = new MapView(centralWidget);
        m_mapview->setObjectName(QStringLiteral("m_mapview"));

        verticalLayout->addWidget(m_mapview);

        ScanView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScanView);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1186, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        ScanView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScanView);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(40, 24));
        mainToolBar->setFloatable(false);
        ScanView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScanView);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScanView->setStatusBar(statusBar);
        m_sensor_dock = new QDockWidget(ScanView);
        m_sensor_dock->setObjectName(QStringLiteral("m_sensor_dock"));
        sensors = new sensor_controls();
        sensors->setObjectName(QStringLiteral("sensors"));
        m_sensor_dock->setWidget(sensors);
        ScanView->addDockWidget(static_cast<Qt::DockWidgetArea>(1), m_sensor_dock);
        console_dock = new QDockWidget(ScanView);
        console_dock->setObjectName(QStringLiteral("console_dock"));
        console = new console_view();
        console->setObjectName(QStringLiteral("console"));
        console_dock->setWidget(console);
        ScanView->addDockWidget(static_cast<Qt::DockWidgetArea>(8), console_dock);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Configuration);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionSave_Configuration);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_2);
        menuTools->addSeparator();
        menuTools->addAction(actionPreferences);
        menuHelp->addAction(actionAbout_Scanview);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRestartCtrlmod);
        mainToolBar->addAction(actionUpdateFirmware);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGetLog);
        mainToolBar->addAction(actionRemoveLogs);

        retranslateUi(ScanView);

        QMetaObject::connectSlotsByName(ScanView);
    } // setupUi

    void retranslateUi(QMainWindow *ScanView)
    {
        ScanView->setWindowTitle(QApplication::translate("ScanView", "ScanView", 0));
        actionClose->setText(QApplication::translate("ScanView", "Open Configuration", 0));
        actionPreferences->setText(QApplication::translate("ScanView", "Preferences", 0));
        actionSave_Configuration->setText(QApplication::translate("ScanView", "Save Configuration", 0));
        actionClose_2->setText(QApplication::translate("ScanView", "Close", 0));
        actionNew_Configuration->setText(QApplication::translate("ScanView", "New Configuration", 0));
        actionAbout_Scanview->setText(QApplication::translate("ScanView", "About Scanview", 0));
        actionConnect->setText(QApplication::translate("ScanView", "connect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("ScanView", "Connect to ctrlmod service running on the edison", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("ScanView", "disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("ScanView", "Disconnect from ctrlmod service", 0));
#endif // QT_NO_TOOLTIP
        actionUpdateFirmware->setText(QApplication::translate("ScanView", "UpdateFirmware", 0));
#ifndef QT_NO_TOOLTIP
        actionUpdateFirmware->setToolTip(QApplication::translate("ScanView", "Update edison firmware", 0));
#endif // QT_NO_TOOLTIP
        actionRestartCtrlmod->setText(QApplication::translate("ScanView", "RestartCtrlmod", 0));
#ifndef QT_NO_TOOLTIP
        actionRestartCtrlmod->setToolTip(QApplication::translate("ScanView", "Restart the ctrlmod service on the edison", 0));
#endif // QT_NO_TOOLTIP
        actionGetLog->setText(QApplication::translate("ScanView", "GetLog", 0));
#ifndef QT_NO_TOOLTIP
        actionGetLog->setToolTip(QApplication::translate("ScanView", "Get the log files from the edison", 0));
#endif // QT_NO_TOOLTIP
        actionRemoveLogs->setText(QApplication::translate("ScanView", "RemoveLogs", 0));
#ifndef QT_NO_TOOLTIP
        actionRemoveLogs->setToolTip(QApplication::translate("ScanView", "Delete log files on edison", 0));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("ScanView", "File", 0));
        menuTools->setTitle(QApplication::translate("ScanView", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("ScanView", "Help", 0));
        m_sensor_dock->setWindowTitle(QApplication::translate("ScanView", "Sensors", 0));
        console_dock->setWindowTitle(QApplication::translate("ScanView", "Console", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanView: public Ui_ScanView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANVIEW_H
