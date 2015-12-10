/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label;
    QLineEdit *projectName_edit;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_2;
    QSpinBox *recTime_sbox;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_3;
    QComboBox *serialPort_cbox;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_4;
    QComboBox *channels_cbox;
    QSpacerItem *horizontalSpacer_19;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QTableWidget *sensitivity_table;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label_5;
    QComboBox *baudRate_cbox;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_24;
    QLabel *label_6;
    QComboBox *parity_cbox;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_26;
    QLabel *label_7;
    QComboBox *flowControl_cbox;
    QSpacerItem *horizontalSpacer_25;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_27;
    QPushButton *acceptSettings_button;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *cancelSettings_button;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->resize(400, 502);
        verticalLayoutWidget = new QWidget(settings);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_13 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        projectName_edit = new QLineEdit(verticalLayoutWidget);
        projectName_edit->setObjectName(QStringLiteral("projectName_edit"));

        horizontalLayout->addWidget(projectName_edit);

        horizontalSpacer_14 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_16 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_16);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        recTime_sbox = new QSpinBox(verticalLayoutWidget);
        recTime_sbox->setObjectName(QStringLiteral("recTime_sbox"));
        recTime_sbox->setMinimum(1);
        recTime_sbox->setMaximum(600);

        horizontalLayout_3->addWidget(recTime_sbox);

        horizontalSpacer_15 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_15);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_18 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_18);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        serialPort_cbox = new QComboBox(verticalLayoutWidget);
        serialPort_cbox->setObjectName(QStringLiteral("serialPort_cbox"));

        horizontalLayout_4->addWidget(serialPort_cbox);

        horizontalSpacer_17 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_17);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_20 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_20);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        channels_cbox = new QComboBox(verticalLayoutWidget);
        channels_cbox->setObjectName(QStringLiteral("channels_cbox"));

        horizontalLayout_5->addWidget(channels_cbox);

        horizontalSpacer_19 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_19);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        sensitivity_table = new QTableWidget(verticalLayoutWidget);
        sensitivity_table->setObjectName(QStringLiteral("sensitivity_table"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sensitivity_table->sizePolicy().hasHeightForWidth());
        sensitivity_table->setSizePolicy(sizePolicy);
        sensitivity_table->setMinimumSize(QSize(0, 150));
        sensitivity_table->setMaximumSize(QSize(16777215, 200));

        horizontalLayout_6->addWidget(sensitivity_table);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_22 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_22);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        baudRate_cbox = new QComboBox(verticalLayoutWidget);
        baudRate_cbox->setObjectName(QStringLiteral("baudRate_cbox"));

        horizontalLayout_7->addWidget(baudRate_cbox);

        horizontalSpacer_21 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_21);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_24 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_24);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        parity_cbox = new QComboBox(verticalLayoutWidget);
        parity_cbox->setObjectName(QStringLiteral("parity_cbox"));

        horizontalLayout_8->addWidget(parity_cbox);

        horizontalSpacer_23 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_23);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_26 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_26);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        flowControl_cbox = new QComboBox(verticalLayoutWidget);
        flowControl_cbox->setObjectName(QStringLiteral("flowControl_cbox"));

        horizontalLayout_2->addWidget(flowControl_cbox);

        horizontalSpacer_25 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_25);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_27);

        acceptSettings_button = new QPushButton(verticalLayoutWidget);
        acceptSettings_button->setObjectName(QStringLiteral("acceptSettings_button"));

        horizontalLayout_9->addWidget(acceptSettings_button);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        cancelSettings_button = new QPushButton(verticalLayoutWidget);
        cancelSettings_button->setObjectName(QStringLiteral("cancelSettings_button"));

        horizontalLayout_9->addWidget(cancelSettings_button);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_9);


        retranslateUi(settings);

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Dialog", 0));
        label->setText(QApplication::translate("settings", "Project Name", 0));
        label_2->setText(QApplication::translate("settings", "Recording Time (seconds)", 0));
        label_3->setText(QApplication::translate("settings", "Serial Port", 0));
        label_4->setText(QApplication::translate("settings", "Number of Channels", 0));
        channels_cbox->clear();
        channels_cbox->insertItems(0, QStringList()
         << QApplication::translate("settings", "1", 0)
         << QApplication::translate("settings", "2", 0)
         << QApplication::translate("settings", "3", 0)
         << QApplication::translate("settings", "4", 0)
         << QApplication::translate("settings", "5", 0)
         << QApplication::translate("settings", "6", 0)
         << QApplication::translate("settings", "7", 0)
        );
        label_5->setText(QApplication::translate("settings", "Baudrate", 0));
        baudRate_cbox->clear();
        baudRate_cbox->insertItems(0, QStringList()
         << QApplication::translate("settings", "115200", 0)
         << QApplication::translate("settings", "custom", 0)
        );
        label_6->setText(QApplication::translate("settings", "Parity", 0));
        parity_cbox->clear();
        parity_cbox->insertItems(0, QStringList()
         << QApplication::translate("settings", "None", 0)
         << QApplication::translate("settings", "Even", 0)
         << QApplication::translate("settings", "Odd", 0)
         << QApplication::translate("settings", "Mark", 0)
         << QApplication::translate("settings", "Space", 0)
        );
        label_7->setText(QApplication::translate("settings", "Flow Control", 0));
        flowControl_cbox->clear();
        flowControl_cbox->insertItems(0, QStringList()
         << QApplication::translate("settings", "None", 0)
         << QApplication::translate("settings", "RTS/CTS", 0)
         << QApplication::translate("settings", "XON/XOFF", 0)
        );
        acceptSettings_button->setText(QApplication::translate("settings", "Accept", 0));
        cancelSettings_button->setText(QApplication::translate("settings", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
