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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mapview.h>

QT_BEGIN_NAMESPACE

class Ui_ScanView
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *m_address_le;
    QLabel *label;
    QSpinBox *m_port_sb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_listen_btn;
    QPushButton *m_stop_btn;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *m_command_cbox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_send_btn;
    QPlainTextEdit *m_echo_pt;
    MapView *m_mapview;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScanView)
    {
        if (ScanView->objectName().isEmpty())
            ScanView->setObjectName(QStringLiteral("ScanView"));
        ScanView->resize(1024, 679);
        centralWidget = new QWidget(ScanView);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        m_address_le = new QLineEdit(groupBox);
        m_address_le->setObjectName(QStringLiteral("m_address_le"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_address_le);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        m_port_sb = new QSpinBox(groupBox);
        m_port_sb->setObjectName(QStringLiteral("m_port_sb"));
        m_port_sb->setMaximum(16000);
        m_port_sb->setValue(2345);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_port_sb);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_listen_btn = new QPushButton(groupBox);
        m_listen_btn->setObjectName(QStringLiteral("m_listen_btn"));

        horizontalLayout->addWidget(m_listen_btn);

        m_stop_btn = new QPushButton(groupBox);
        m_stop_btn->setObjectName(QStringLiteral("m_stop_btn"));

        horizontalLayout->addWidget(m_stop_btn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_command_cbox = new QComboBox(groupBox_2);
        m_command_cbox->setObjectName(QStringLiteral("m_command_cbox"));

        verticalLayout_2->addWidget(m_command_cbox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_send_btn = new QPushButton(groupBox_2);
        m_send_btn->setObjectName(QStringLiteral("m_send_btn"));

        horizontalLayout_2->addWidget(m_send_btn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        m_echo_pt = new QPlainTextEdit(groupBox_2);
        m_echo_pt->setObjectName(QStringLiteral("m_echo_pt"));
        m_echo_pt->setReadOnly(true);

        verticalLayout_2->addWidget(m_echo_pt);


        verticalLayout_3->addWidget(groupBox_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        m_mapview = new MapView(centralWidget);
        m_mapview->setObjectName(QStringLiteral("m_mapview"));
        m_mapview->setMinimumSize(QSize(800, 600));

        horizontalLayout_3->addWidget(m_mapview);

        ScanView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScanView);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 22));
        ScanView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScanView);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScanView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScanView);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScanView->setStatusBar(statusBar);

        retranslateUi(ScanView);
        QObject::connect(m_listen_btn, SIGNAL(pressed()), ScanView, SLOT(onListen()));
        QObject::connect(m_stop_btn, SIGNAL(pressed()), ScanView, SLOT(onStop()));
        QObject::connect(m_send_btn, SIGNAL(pressed()), ScanView, SLOT(onSendCommand()));

        QMetaObject::connectSlotsByName(ScanView);
    } // setupUi

    void retranslateUi(QMainWindow *ScanView)
    {
        ScanView->setWindowTitle(QApplication::translate("ScanView", "ScanView", 0));
        groupBox->setTitle(QApplication::translate("ScanView", "Connection Settings", 0));
        label_2->setText(QApplication::translate("ScanView", "Address", 0));
        label->setText(QApplication::translate("ScanView", "Port", 0));
        m_listen_btn->setText(QApplication::translate("ScanView", "Open", 0));
        m_stop_btn->setText(QApplication::translate("ScanView", "Close", 0));
        groupBox_2->setTitle(QApplication::translate("ScanView", "RPLidar Commands", 0));
        m_command_cbox->clear();
        m_command_cbox->insertItems(0, QStringList()
         << QApplication::translate("ScanView", "Get Device Health", 0)
         << QApplication::translate("ScanView", "Get Device Information", 0)
         << QApplication::translate("ScanView", "Start Scan", 0)
         << QApplication::translate("ScanView", "Force Scan", 0)
         << QApplication::translate("ScanView", "Stop Scan", 0)
         << QApplication::translate("ScanView", "Reset", 0)
        );
        m_send_btn->setText(QApplication::translate("ScanView", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanView: public Ui_ScanView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANVIEW_H
