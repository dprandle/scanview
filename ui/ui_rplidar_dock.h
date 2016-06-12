/********************************************************************************
** Form generated from reading UI file 'rplidar_dock.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPLIDAR_DOCK_H
#define UI_RPLIDAR_DOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rplidar_dock
{
public:
    QWidget *rplidar_widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QComboBox *m_command_cbox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_send_btn;
    QPlainTextEdit *m_rplidar_pt;

    void setupUi(QDockWidget *rplidar_dock)
    {
        if (rplidar_dock->objectName().isEmpty())
            rplidar_dock->setObjectName(QStringLiteral("rplidar_dock"));
        rplidar_dock->resize(295, 322);
        rplidar_widget = new QWidget();
        rplidar_widget->setObjectName(QStringLiteral("rplidar_widget"));
        verticalLayout = new QVBoxLayout(rplidar_widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_10 = new QLabel(rplidar_widget);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_10);

        m_command_cbox = new QComboBox(rplidar_widget);
        m_command_cbox->setObjectName(QStringLiteral("m_command_cbox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_command_cbox->sizePolicy().hasHeightForWidth());
        m_command_cbox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(m_command_cbox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_send_btn = new QPushButton(rplidar_widget);
        m_send_btn->setObjectName(QStringLiteral("m_send_btn"));

        horizontalLayout_2->addWidget(m_send_btn);


        verticalLayout->addLayout(horizontalLayout_2);

        m_rplidar_pt = new QPlainTextEdit(rplidar_widget);
        m_rplidar_pt->setObjectName(QStringLiteral("m_rplidar_pt"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_rplidar_pt->sizePolicy().hasHeightForWidth());
        m_rplidar_pt->setSizePolicy(sizePolicy2);
        m_rplidar_pt->setReadOnly(true);

        verticalLayout->addWidget(m_rplidar_pt);

        rplidar_dock->setWidget(rplidar_widget);

        retranslateUi(rplidar_dock);

        QMetaObject::connectSlotsByName(rplidar_dock);
    } // setupUi

    void retranslateUi(QDockWidget *rplidar_dock)
    {
        rplidar_dock->setWindowTitle(QApplication::translate("rplidar_dock", "RPLidar Controls", 0));
        label_10->setText(QApplication::translate("rplidar_dock", "Command", 0));
        m_command_cbox->clear();
        m_command_cbox->insertItems(0, QStringList()
         << QApplication::translate("rplidar_dock", "Get Device Health", 0)
         << QApplication::translate("rplidar_dock", "Get Device Information", 0)
         << QApplication::translate("rplidar_dock", "Start Scan", 0)
         << QApplication::translate("rplidar_dock", "Force Scan", 0)
         << QApplication::translate("rplidar_dock", "Stop Scan", 0)
         << QApplication::translate("rplidar_dock", "Reset", 0)
        );
        m_send_btn->setText(QApplication::translate("rplidar_dock", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class rplidar_dock: public Ui_rplidar_dock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPLIDAR_DOCK_H
