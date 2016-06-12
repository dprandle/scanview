/********************************************************************************
** Form generated from reading UI file 'rplidar_controls.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPLIDAR_CONTROLS_H
#define UI_RPLIDAR_CONTROLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rplidar_controls
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QComboBox *m_command_cbox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_send_btn;

    void setupUi(QWidget *rplidar_controls)
    {
        if (rplidar_controls->objectName().isEmpty())
            rplidar_controls->setObjectName(QStringLiteral("rplidar_controls"));
        rplidar_controls->resize(298, 78);
        verticalLayout = new QVBoxLayout(rplidar_controls);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_10 = new QLabel(rplidar_controls);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_10);

        m_command_cbox = new QComboBox(rplidar_controls);
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

        m_send_btn = new QPushButton(rplidar_controls);
        m_send_btn->setObjectName(QStringLiteral("m_send_btn"));

        horizontalLayout_2->addWidget(m_send_btn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(rplidar_controls);

        QMetaObject::connectSlotsByName(rplidar_controls);
    } // setupUi

    void retranslateUi(QWidget *rplidar_controls)
    {
        rplidar_controls->setWindowTitle(QApplication::translate("rplidar_controls", "Form", 0));
        label_10->setText(QApplication::translate("rplidar_controls", "Command", 0));
        m_command_cbox->clear();
        m_command_cbox->insertItems(0, QStringList()
         << QApplication::translate("rplidar_controls", "Get Device Health", 0)
         << QApplication::translate("rplidar_controls", "Get Device Information", 0)
         << QApplication::translate("rplidar_controls", "Start Scan", 0)
         << QApplication::translate("rplidar_controls", "Force Scan", 0)
         << QApplication::translate("rplidar_controls", "Stop Scan", 0)
         << QApplication::translate("rplidar_controls", "Reset", 0)
        );
        m_send_btn->setText(QApplication::translate("rplidar_controls", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class rplidar_controls: public Ui_rplidar_controls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPLIDAR_CONTROLS_H
