/********************************************************************************
** Form generated from reading UI file 'saveProject.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEPROJECT_H
#define UI_SAVEPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saveProject
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *ProjectNameSaveEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *txtSave;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *AcceptSaveButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *CancelSaveButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *saveProject)
    {
        if (saveProject->objectName().isEmpty())
            saveProject->setObjectName(QStringLiteral("saveProject"));
        saveProject->resize(400, 145);
        verticalLayoutWidget = new QWidget(saveProject);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(50, 20));

        verticalLayout->addWidget(label);

        ProjectNameSaveEdit = new QLineEdit(verticalLayoutWidget);
        ProjectNameSaveEdit->setObjectName(QStringLiteral("ProjectNameSaveEdit"));

        verticalLayout->addWidget(ProjectNameSaveEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        txtSave = new QRadioButton(verticalLayoutWidget);
        txtSave->setObjectName(QStringLiteral("txtSave"));

        horizontalLayout_2->addWidget(txtSave);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        AcceptSaveButton = new QPushButton(verticalLayoutWidget);
        AcceptSaveButton->setObjectName(QStringLiteral("AcceptSaveButton"));

        horizontalLayout->addWidget(AcceptSaveButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        CancelSaveButton = new QPushButton(verticalLayoutWidget);
        CancelSaveButton->setObjectName(QStringLiteral("CancelSaveButton"));

        horizontalLayout->addWidget(CancelSaveButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(saveProject);

        QMetaObject::connectSlotsByName(saveProject);
    } // setupUi

    void retranslateUi(QDialog *saveProject)
    {
        saveProject->setWindowTitle(QApplication::translate("saveProject", "Dialog", 0));
        label->setText(QApplication::translate("saveProject", "Save project as:", 0));
        txtSave->setText(QApplication::translate("saveProject", "Save .txt file for further processing", 0));
        AcceptSaveButton->setText(QApplication::translate("saveProject", "Accept", 0));
        CancelSaveButton->setText(QApplication::translate("saveProject", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class saveProject: public Ui_saveProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEPROJECT_H
