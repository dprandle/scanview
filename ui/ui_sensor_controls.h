/********************************************************************************
** Form generated from reading UI file 'sensor_controls.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSOR_CONTROLS_H
#define UI_SENSOR_CONTROLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sensor_controls
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *m_alt_P_sb;
    QDoubleSpinBox *m_alt_I_sb;
    QDoubleSpinBox *m_alt_D_sb;
    QLabel *label_6;
    QSpinBox *m_alt_ramp_sb;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *m_bias_x_sb;
    QDoubleSpinBox *m_bias_y_sb;
    QLabel *label_12;
    QSpinBox *m_bias_threshold_sb;
    QLabel *label_11;
    QDoubleSpinBox *m_g_factor_sb;
    QLabel *label_13;
    QCheckBox *m_threshold_dropout_cb;
    QLabel *label_8;
    QCheckBox *m_ant_reset_windup_cb;
    QLabel *label_9;
    QCheckBox *m_complex_der_cb;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *m_command_cbox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_send_btn;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_3;
    QLabel *label_3;
    QLineEdit *m_ceiling_le;
    QLabel *label_4;
    QLineEdit *m_floor_le;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *sensor_controls)
    {
        if (sensor_controls->objectName().isEmpty())
            sensor_controls->setObjectName(QStringLiteral("sensor_controls"));
        sensor_controls->resize(513, 521);
        verticalLayout_4 = new QVBoxLayout(sensor_controls);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(sensor_controls);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_alt_P_sb = new QDoubleSpinBox(groupBox);
        m_alt_P_sb->setObjectName(QStringLiteral("m_alt_P_sb"));
        m_alt_P_sb->setMaximum(100);
        m_alt_P_sb->setSingleStep(0.1);
        m_alt_P_sb->setValue(1);

        horizontalLayout_6->addWidget(m_alt_P_sb);

        m_alt_I_sb = new QDoubleSpinBox(groupBox);
        m_alt_I_sb->setObjectName(QStringLiteral("m_alt_I_sb"));
        m_alt_I_sb->setMaximum(10);
        m_alt_I_sb->setSingleStep(0.01);

        horizontalLayout_6->addWidget(m_alt_I_sb);

        m_alt_D_sb = new QDoubleSpinBox(groupBox);
        m_alt_D_sb->setObjectName(QStringLiteral("m_alt_D_sb"));
        m_alt_D_sb->setMaximum(100);
        m_alt_D_sb->setSingleStep(0.1);

        horizontalLayout_6->addWidget(m_alt_D_sb);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_6);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        m_alt_ramp_sb = new QSpinBox(groupBox);
        m_alt_ramp_sb->setObjectName(QStringLiteral("m_alt_ramp_sb"));
        m_alt_ramp_sb->setMaximum(100);
        m_alt_ramp_sb->setValue(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_alt_ramp_sb);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_bias_x_sb = new QDoubleSpinBox(groupBox);
        m_bias_x_sb->setObjectName(QStringLiteral("m_bias_x_sb"));
        m_bias_x_sb->setMaximum(5000);

        horizontalLayout_7->addWidget(m_bias_x_sb);

        m_bias_y_sb = new QDoubleSpinBox(groupBox);
        m_bias_y_sb->setObjectName(QStringLiteral("m_bias_y_sb"));
        m_bias_y_sb->setMaximum(5000);
        m_bias_y_sb->setValue(0);

        horizontalLayout_7->addWidget(m_bias_y_sb);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_7);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_12);

        m_bias_threshold_sb = new QSpinBox(groupBox);
        m_bias_threshold_sb->setObjectName(QStringLiteral("m_bias_threshold_sb"));
        m_bias_threshold_sb->setMaximum(10000);
        m_bias_threshold_sb->setSingleStep(10);

        formLayout->setWidget(3, QFormLayout::FieldRole, m_bias_threshold_sb);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_11);

        m_g_factor_sb = new QDoubleSpinBox(groupBox);
        m_g_factor_sb->setObjectName(QStringLiteral("m_g_factor_sb"));
        m_g_factor_sb->setMaximum(100);
        m_g_factor_sb->setSingleStep(0.01);
        m_g_factor_sb->setValue(1);

        formLayout->setWidget(4, QFormLayout::FieldRole, m_g_factor_sb);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_13);

        m_threshold_dropout_cb = new QCheckBox(groupBox);
        m_threshold_dropout_cb->setObjectName(QStringLiteral("m_threshold_dropout_cb"));
        m_threshold_dropout_cb->setLayoutDirection(Qt::RightToLeft);

        formLayout->setWidget(5, QFormLayout::FieldRole, m_threshold_dropout_cb);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_8);

        m_ant_reset_windup_cb = new QCheckBox(groupBox);
        m_ant_reset_windup_cb->setObjectName(QStringLiteral("m_ant_reset_windup_cb"));
        m_ant_reset_windup_cb->setLayoutDirection(Qt::RightToLeft);
        m_ant_reset_windup_cb->setChecked(true);

        formLayout->setWidget(6, QFormLayout::FieldRole, m_ant_reset_windup_cb);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_9);

        m_complex_der_cb = new QCheckBox(groupBox);
        m_complex_der_cb->setObjectName(QStringLiteral("m_complex_der_cb"));
        m_complex_der_cb->setLayoutDirection(Qt::RightToLeft);
        m_complex_der_cb->setChecked(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, m_complex_der_cb);


        verticalLayout->addLayout(formLayout);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(sensor_controls);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_command_cbox = new QComboBox(groupBox_2);
        m_command_cbox->setObjectName(QStringLiteral("m_command_cbox"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_command_cbox->sizePolicy().hasHeightForWidth());
        m_command_cbox->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(m_command_cbox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_send_btn = new QPushButton(groupBox_2);
        m_send_btn->setObjectName(QStringLiteral("m_send_btn"));

        horizontalLayout->addWidget(m_send_btn);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(sensor_controls);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_3);

        m_ceiling_le = new QLineEdit(groupBox_3);
        m_ceiling_le->setObjectName(QStringLiteral("m_ceiling_le"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_ceiling_le->sizePolicy().hasHeightForWidth());
        m_ceiling_le->setSizePolicy(sizePolicy1);
        m_ceiling_le->setReadOnly(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, m_ceiling_le);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_4);

        m_floor_le = new QLineEdit(groupBox_3);
        m_floor_le->setObjectName(QStringLiteral("m_floor_le"));
        sizePolicy1.setHeightForWidth(m_floor_le->sizePolicy().hasHeightForWidth());
        m_floor_le->setSizePolicy(sizePolicy1);
        m_floor_le->setReadOnly(true);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, m_floor_le);


        verticalLayout_3->addLayout(formLayout_3);


        verticalLayout_4->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        retranslateUi(sensor_controls);
        QObject::connect(m_alt_D_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_alt_I_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_alt_P_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_alt_ramp_sb, SIGNAL(valueChanged(int)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_bias_y_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_bias_x_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_bias_threshold_sb, SIGNAL(valueChanged(int)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_g_factor_sb, SIGNAL(valueChanged(double)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_threshold_dropout_cb, SIGNAL(toggled(bool)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_ant_reset_windup_cb, SIGNAL(toggled(bool)), sensor_controls, SLOT(on_edit()));
        QObject::connect(m_complex_der_cb, SIGNAL(toggled(bool)), sensor_controls, SLOT(on_edit()));

        QMetaObject::connectSlotsByName(sensor_controls);
    } // setupUi

    void retranslateUi(QWidget *sensor_controls)
    {
        sensor_controls->setWindowTitle(QApplication::translate("sensor_controls", "Form", 0));
        groupBox->setTitle(QApplication::translate("sensor_controls", "Navigation Parameters", 0));
        label_5->setText(QApplication::translate("sensor_controls", "PID Gain", 0));
        label_6->setText(QApplication::translate("sensor_controls", "Ramp Limit (%)", 0));
        label_7->setText(QApplication::translate("sensor_controls", "Bias Vector (X Y)", 0));
        label_12->setText(QApplication::translate("sensor_controls", "Bias Threshold Dist", 0));
        label_11->setText(QApplication::translate("sensor_controls", "G Factor", 0));
        label_13->setText(QApplication::translate("sensor_controls", "Threshold Dropout", 0));
        m_threshold_dropout_cb->setText(QString());
        label_8->setText(QApplication::translate("sensor_controls", "Anit-reset Windup", 0));
        m_ant_reset_windup_cb->setText(QString());
        label_9->setText(QApplication::translate("sensor_controls", "Complex Derivitive", 0));
        m_complex_der_cb->setText(QString());
        groupBox_2->setTitle(QApplication::translate("sensor_controls", "Lidar Commands", 0));
        m_command_cbox->clear();
        m_command_cbox->insertItems(0, QStringList()
         << QApplication::translate("sensor_controls", "Get Device Health", 0)
         << QApplication::translate("sensor_controls", "Get Device Information", 0)
         << QApplication::translate("sensor_controls", "Start Scan", 0)
         << QApplication::translate("sensor_controls", "Force Scan", 0)
         << QApplication::translate("sensor_controls", "Stop Scan", 0)
         << QApplication::translate("sensor_controls", "Reset", 0)
        );
        m_send_btn->setText(QApplication::translate("sensor_controls", "Send", 0));
        groupBox_3->setTitle(QApplication::translate("sensor_controls", "Pulsed Light Sensors", 0));
        label_3->setText(QApplication::translate("sensor_controls", "Ceiling Distance", 0));
        label_4->setText(QApplication::translate("sensor_controls", "Floor Distance", 0));
    } // retranslateUi

};

namespace Ui {
    class sensor_controls: public Ui_sensor_controls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSOR_CONTROLS_H
