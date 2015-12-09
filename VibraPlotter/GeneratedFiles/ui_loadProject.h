/********************************************************************************
** Form generated from reading UI file 'loadProject.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADPROJECT_H
#define UI_LOADPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadProject
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableProjects;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *AcceptLoadButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *CancelLoadButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *loadProject)
    {
        if (loadProject->objectName().isEmpty())
            loadProject->setObjectName(QStringLiteral("loadProject"));
        loadProject->resize(400, 294);
        verticalLayoutWidget = new QWidget(loadProject);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 9, 381, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(200, 20));

        verticalLayout->addWidget(label);

        tableProjects = new QTableWidget(verticalLayoutWidget);
        tableProjects->setObjectName(QStringLiteral("tableProjects"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableProjects->sizePolicy().hasHeightForWidth());
        tableProjects->setSizePolicy(sizePolicy1);
        tableProjects->setMinimumSize(QSize(150, 20));
        tableProjects->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout->addWidget(tableProjects);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        AcceptLoadButton = new QPushButton(verticalLayoutWidget);
        AcceptLoadButton->setObjectName(QStringLiteral("AcceptLoadButton"));

        horizontalLayout->addWidget(AcceptLoadButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        CancelLoadButton = new QPushButton(verticalLayoutWidget);
        CancelLoadButton->setObjectName(QStringLiteral("CancelLoadButton"));

        horizontalLayout->addWidget(CancelLoadButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(loadProject);

        QMetaObject::connectSlotsByName(loadProject);
    } // setupUi

    void retranslateUi(QDialog *loadProject)
    {
        loadProject->setWindowTitle(QApplication::translate("loadProject", "Dialog", 0));
        label->setText(QApplication::translate("loadProject", "Select a saved project from the list:", 0));
        AcceptLoadButton->setText(QApplication::translate("loadProject", "Accept", 0));
        CancelLoadButton->setText(QApplication::translate("loadProject", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class loadProject: public Ui_loadProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADPROJECT_H
