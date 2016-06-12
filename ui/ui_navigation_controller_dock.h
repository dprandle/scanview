/********************************************************************************
** Form generated from reading UI file 'navigation_controller_dock.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIGATION_CONTROLLER_DOCK_H
#define UI_NAVIGATION_CONTROLLER_DOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_navigation_controller_dock
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *m_alt_P_sb;
    QDoubleSpinBox *m_alt_I_sb;
    QDoubleSpinBox *m_alt_D_sb;
    QLabel *label_6;
    QSpinBox *m_alt_ramp_sb;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *m_bias_x_sb;
    QDoubleSpinBox *m_bias_y_sb;
    QLabel *label_8;
    QCheckBox *m_ant_reset_windup_cb;
    QLabel *label_9;
    QCheckBox *m_complex_der_cb;
    QLabel *label_11;
    QDoubleSpinBox *m_g_factor_sb;
    QLabel *label_12;
    QSpinBox *m_bias_threshold_sb;
    QCheckBox *m_threshold_dropout_cb;
    QLabel *label_13;

    void setupUi(QDockWidget *navigation_controller_dock)
    {
        if (navigation_controller_dock->objectName().isEmpty())
            navigation_controller_dock->setObjectName(QStringLiteral("navigation_controller_dock"));
        navigation_controller_dock->resize(377, 281);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_5 = new QLabel(dockWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_alt_P_sb = new QDoubleSpinBox(dockWidgetContents);
        m_alt_P_sb->setObjectName(QStringLiteral("m_alt_P_sb"));
        m_alt_P_sb->setMaximum(100);
        m_alt_P_sb->setSingleStep(0.1);
        m_alt_P_sb->setValue(1);

        horizontalLayout_4->addWidget(m_alt_P_sb);

        m_alt_I_sb = new QDoubleSpinBox(dockWidgetContents);
        m_alt_I_sb->setObjectName(QStringLiteral("m_alt_I_sb"));
        m_alt_I_sb->setMaximum(10);
        m_alt_I_sb->setSingleStep(0.01);

        horizontalLayout_4->addWidget(m_alt_I_sb);

        m_alt_D_sb = new QDoubleSpinBox(dockWidgetContents);
        m_alt_D_sb->setObjectName(QStringLiteral("m_alt_D_sb"));
        m_alt_D_sb->setMaximum(100);
        m_alt_D_sb->setSingleStep(0.1);

        horizontalLayout_4->addWidget(m_alt_D_sb);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        label_6 = new QLabel(dockWidgetContents);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        m_alt_ramp_sb = new QSpinBox(dockWidgetContents);
        m_alt_ramp_sb->setObjectName(QStringLiteral("m_alt_ramp_sb"));
        m_alt_ramp_sb->setMaximum(100);
        m_alt_ramp_sb->setValue(100);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_alt_ramp_sb);

        label_7 = new QLabel(dockWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_bias_x_sb = new QDoubleSpinBox(dockWidgetContents);
        m_bias_x_sb->setObjectName(QStringLiteral("m_bias_x_sb"));
        m_bias_x_sb->setMaximum(5000);

        horizontalLayout_5->addWidget(m_bias_x_sb);

        m_bias_y_sb = new QDoubleSpinBox(dockWidgetContents);
        m_bias_y_sb->setObjectName(QStringLiteral("m_bias_y_sb"));
        m_bias_y_sb->setMaximum(5000);
        m_bias_y_sb->setValue(0);

        horizontalLayout_5->addWidget(m_bias_y_sb);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout_5);

        label_8 = new QLabel(dockWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_8);

        m_ant_reset_windup_cb = new QCheckBox(dockWidgetContents);
        m_ant_reset_windup_cb->setObjectName(QStringLiteral("m_ant_reset_windup_cb"));
        m_ant_reset_windup_cb->setLayoutDirection(Qt::RightToLeft);
        m_ant_reset_windup_cb->setChecked(true);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, m_ant_reset_windup_cb);

        label_9 = new QLabel(dockWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_9);

        m_complex_der_cb = new QCheckBox(dockWidgetContents);
        m_complex_der_cb->setObjectName(QStringLiteral("m_complex_der_cb"));
        m_complex_der_cb->setLayoutDirection(Qt::RightToLeft);
        m_complex_der_cb->setChecked(true);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, m_complex_der_cb);

        label_11 = new QLabel(dockWidgetContents);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_11);

        m_g_factor_sb = new QDoubleSpinBox(dockWidgetContents);
        m_g_factor_sb->setObjectName(QStringLiteral("m_g_factor_sb"));
        m_g_factor_sb->setMaximum(100);
        m_g_factor_sb->setSingleStep(0.01);
        m_g_factor_sb->setValue(1);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, m_g_factor_sb);

        label_12 = new QLabel(dockWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_12);

        m_bias_threshold_sb = new QSpinBox(dockWidgetContents);
        m_bias_threshold_sb->setObjectName(QStringLiteral("m_bias_threshold_sb"));
        m_bias_threshold_sb->setMaximum(10000);
        m_bias_threshold_sb->setSingleStep(10);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, m_bias_threshold_sb);

        m_threshold_dropout_cb = new QCheckBox(dockWidgetContents);
        m_threshold_dropout_cb->setObjectName(QStringLiteral("m_threshold_dropout_cb"));
        m_threshold_dropout_cb->setLayoutDirection(Qt::RightToLeft);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, m_threshold_dropout_cb);

        label_13 = new QLabel(dockWidgetContents);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_13);


        verticalLayout->addLayout(formLayout_2);

        navigation_controller_dock->setWidget(dockWidgetContents);

        retranslateUi(navigation_controller_dock);
        QObject::connect(m_alt_P_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_alt_I_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_alt_D_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_alt_ramp_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_bias_x_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_bias_y_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_bias_threshold_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_g_factor_sb, SIGNAL(editingFinished()), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_threshold_dropout_cb, SIGNAL(toggled(bool)), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_ant_reset_windup_cb, SIGNAL(toggled(bool)), navigation_controller_dock, SLOT(on_edit()));
        QObject::connect(m_complex_der_cb, SIGNAL(toggled(bool)), navigation_controller_dock, SLOT(on_edit()));

        QMetaObject::connectSlotsByName(navigation_controller_dock);
    } // setupUi

    void retranslateUi(QDockWidget *navigation_controller_dock)
    {
        navigation_controller_dock->setWindowTitle(QApplication::translate("navigation_controller_dock", "Navigation", 0));
        label_5->setText(QApplication::translate("navigation_controller_dock", "PID Gain", 0));
        label_6->setText(QApplication::translate("navigation_controller_dock", "Ramp Limit (%)", 0));
        label_7->setText(QApplication::translate("navigation_controller_dock", "Bias Vector (X Y)", 0));
        label_8->setText(QApplication::translate("navigation_controller_dock", "Anit-reset Windup", 0));
        m_ant_reset_windup_cb->setText(QString());
        label_9->setText(QApplication::translate("navigation_controller_dock", "Complex Derivitive", 0));
        m_complex_der_cb->setText(QString());
        label_11->setText(QApplication::translate("navigation_controller_dock", "G Factor", 0));
        label_12->setText(QApplication::translate("navigation_controller_dock", "Bias Threshold Dist", 0));
        m_threshold_dropout_cb->setText(QString());
        label_13->setText(QApplication::translate("navigation_controller_dock", "Threshold Dropout", 0));
    } // retranslateUi

};

namespace Ui {
    class navigation_controller_dock: public Ui_navigation_controller_dock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIGATION_CONTROLLER_DOCK_H
