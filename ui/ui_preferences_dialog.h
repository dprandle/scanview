/********************************************************************************
** Form generated from reading UI file 'preferences_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_DIALOG_H
#define UI_PREFERENCES_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preferences_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *conn;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_3;
    QLabel *label_3;
    QLineEdit *le_username;
    QLabel *label_4;
    QLineEdit *le_password;
    QLabel *label;
    QLineEdit *le_host_name;
    QLabel *label_5;
    QSpinBox *sb_port;
    QGroupBox *gb_host_ip;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *le_host_ip;
    QSpacerItem *verticalSpacer;
    QWidget *dirs;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *le_edison_firmware;
    QToolButton *tbtn_edison_logs_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_config_files;
    QToolButton *tbtn_config_files;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_edison_log;
    QToolButton *tbtn_edison_logs;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_cancel;
    QPushButton *btn_okay;

    void setupUi(QDialog *preferences_dialog)
    {
        if (preferences_dialog->objectName().isEmpty())
            preferences_dialog->setObjectName(QStringLiteral("preferences_dialog"));
        preferences_dialog->resize(561, 437);
        verticalLayout_2 = new QVBoxLayout(preferences_dialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listWidget = new QListWidget(preferences_dialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/connected.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/directories.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon1);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(200, 0));
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setIconSize(QSize(30, 30));
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setResizeMode(QListView::Fixed);
        listWidget->setGridSize(QSize(0, 35));
        listWidget->setViewMode(QListView::ListMode);

        horizontalLayout_2->addWidget(listWidget);

        stackedWidget = new QStackedWidget(preferences_dialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(200, 0));
        conn = new QWidget();
        conn->setObjectName(QStringLiteral("conn"));
        verticalLayout = new QVBoxLayout(conn);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_3 = new QLabel(conn);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_3);

        le_username = new QLineEdit(conn);
        le_username->setObjectName(QStringLiteral("le_username"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, le_username);

        label_4 = new QLabel(conn);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_4);

        le_password = new QLineEdit(conn);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, le_password);

        label = new QLabel(conn);
        label->setObjectName(QStringLiteral("label"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label);

        le_host_name = new QLineEdit(conn);
        le_host_name->setObjectName(QStringLiteral("le_host_name"));
        le_host_name->setEnabled(false);
        le_host_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, le_host_name);

        label_5 = new QLabel(conn);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_5);

        sb_port = new QSpinBox(conn);
        sb_port->setObjectName(QStringLiteral("sb_port"));
        sb_port->setMaximum(65536);
        sb_port->setValue(3366);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, sb_port);


        verticalLayout->addLayout(formLayout_3);

        gb_host_ip = new QGroupBox(conn);
        gb_host_ip->setObjectName(QStringLiteral("gb_host_ip"));
        gb_host_ip->setCheckable(true);
        gb_host_ip->setChecked(true);
        formLayout = new QFormLayout(gb_host_ip);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(gb_host_ip);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        le_host_ip = new QLineEdit(gb_host_ip);
        le_host_ip->setObjectName(QStringLiteral("le_host_ip"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_host_ip);


        verticalLayout->addWidget(gb_host_ip);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        stackedWidget->addWidget(conn);
        dirs = new QWidget();
        dirs->setObjectName(QStringLiteral("dirs"));
        verticalLayout_3 = new QVBoxLayout(dirs);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_4 = new QGroupBox(dirs);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        le_edison_firmware = new QLineEdit(groupBox_4);
        le_edison_firmware->setObjectName(QStringLiteral("le_edison_firmware"));

        horizontalLayout_5->addWidget(le_edison_firmware);

        tbtn_edison_logs_2 = new QToolButton(groupBox_4);
        tbtn_edison_logs_2->setObjectName(QStringLiteral("tbtn_edison_logs_2"));

        horizontalLayout_5->addWidget(tbtn_edison_logs_2);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(dirs);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        le_config_files = new QLineEdit(groupBox_3);
        le_config_files->setObjectName(QStringLiteral("le_config_files"));
        le_config_files->setReadOnly(true);

        horizontalLayout_3->addWidget(le_config_files);

        tbtn_config_files = new QToolButton(groupBox_3);
        tbtn_config_files->setObjectName(QStringLiteral("tbtn_config_files"));

        horizontalLayout_3->addWidget(tbtn_config_files);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(dirs);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        le_edison_log = new QLineEdit(groupBox_2);
        le_edison_log->setObjectName(QStringLiteral("le_edison_log"));

        horizontalLayout_4->addWidget(le_edison_log);

        tbtn_edison_logs = new QToolButton(groupBox_2);
        tbtn_edison_logs->setObjectName(QStringLiteral("tbtn_edison_logs"));

        horizontalLayout_4->addWidget(tbtn_edison_logs);


        verticalLayout_3->addWidget(groupBox_2);

        verticalSpacer_2 = new QSpacerItem(20, 213, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        stackedWidget->addWidget(dirs);

        horizontalLayout_2->addWidget(stackedWidget);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_cancel = new QPushButton(preferences_dialog);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));

        horizontalLayout->addWidget(btn_cancel);

        btn_okay = new QPushButton(preferences_dialog);
        btn_okay->setObjectName(QStringLiteral("btn_okay"));

        horizontalLayout->addWidget(btn_okay);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(preferences_dialog);
        QObject::connect(btn_cancel, SIGNAL(pressed()), preferences_dialog, SLOT(reject()));
        QObject::connect(btn_okay, SIGNAL(pressed()), preferences_dialog, SLOT(accept()));
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
        QObject::connect(gb_host_ip, SIGNAL(toggled(bool)), preferences_dialog, SLOT(on_toggle_use_ip(bool)));
        QObject::connect(tbtn_config_files, SIGNAL(pressed()), preferences_dialog, SLOT(on_config_files_btn()));
        QObject::connect(tbtn_edison_logs, SIGNAL(pressed()), preferences_dialog, SLOT(on_edison_logs_btn()));
        QObject::connect(tbtn_edison_logs_2, SIGNAL(pressed()), preferences_dialog, SLOT(on_edison_firmware_btn()));

        listWidget->setCurrentRow(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(preferences_dialog);
    } // setupUi

    void retranslateUi(QDialog *preferences_dialog)
    {
        preferences_dialog->setWindowTitle(QApplication::translate("preferences_dialog", "Dialog", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("preferences_dialog", "Edison Connection", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("preferences_dialog", "Directories", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("preferences_dialog", "Edison Username", 0));
        le_username->setText(QApplication::translate("preferences_dialog", "root", 0));
        label_4->setText(QApplication::translate("preferences_dialog", "Edison Password", 0));
        le_password->setText(QApplication::translate("preferences_dialog", "abcd1234", 0));
        label->setText(QApplication::translate("preferences_dialog", "Host Name", 0));
        le_host_name->setText(QApplication::translate("preferences_dialog", "edison", 0));
        label_5->setText(QApplication::translate("preferences_dialog", "Ctrlmod Port", 0));
        gb_host_ip->setTitle(QApplication::translate("preferences_dialog", "Use IP instead of host name", 0));
        label_2->setText(QApplication::translate("preferences_dialog", "Host IP", 0));
        le_host_ip->setText(QApplication::translate("preferences_dialog", "192.168.42.1", 0));
        groupBox_4->setTitle(QApplication::translate("preferences_dialog", "Edison Firmware", 0));
        tbtn_edison_logs_2->setText(QApplication::translate("preferences_dialog", "...", 0));
        groupBox_3->setTitle(QApplication::translate("preferences_dialog", "Config Files", 0));
        tbtn_config_files->setText(QApplication::translate("preferences_dialog", "...", 0));
        groupBox_2->setTitle(QApplication::translate("preferences_dialog", "Edison Logs", 0));
        tbtn_edison_logs->setText(QApplication::translate("preferences_dialog", "...", 0));
        btn_cancel->setText(QApplication::translate("preferences_dialog", "Cancel", 0));
        btn_okay->setText(QApplication::translate("preferences_dialog", "Okay", 0));
    } // retranslateUi

};

namespace Ui {
    class preferences_dialog: public Ui_preferences_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_DIALOG_H
