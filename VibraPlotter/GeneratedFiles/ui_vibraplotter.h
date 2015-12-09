/********************************************************************************
** Form generated from reading UI file 'vibraplotter.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIBRAPLOTTER_H
#define UI_VIBRAPLOTTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_VibraPlotterClass
{
public:
    QAction *actionNewProject;
    QAction *actionLoadProject;
    QAction *actionSettings;
    QAction *actionSaveProject;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *LoadButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *channel_combo_box;
    QVBoxLayout *verticalLayout_5;
    QLabel *CommentsLbl;
    QTextEdit *ChannelComments;
    QCustomPlot *signalPlot;
    QCustomPlot *fourierPlot;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VibraPlotterClass)
    {
        if (VibraPlotterClass->objectName().isEmpty())
            VibraPlotterClass->setObjectName(QStringLiteral("VibraPlotterClass"));
        VibraPlotterClass->resize(892, 807);
        actionNewProject = new QAction(VibraPlotterClass);
        actionNewProject->setObjectName(QStringLiteral("actionNewProject"));
        QIcon icon;
        icon.addFile(QStringLiteral("Icons/New.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewProject->setIcon(icon);
        actionLoadProject = new QAction(VibraPlotterClass);
        actionLoadProject->setObjectName(QStringLiteral("actionLoadProject"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Icons/Load2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadProject->setIcon(icon1);
        actionSettings = new QAction(VibraPlotterClass);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Icons/Settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon2);
        actionSaveProject = new QAction(VibraPlotterClass);
        actionSaveProject->setObjectName(QStringLiteral("actionSaveProject"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Icons/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveProject->setIcon(icon3);
        centralWidget = new QWidget(VibraPlotterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        LoadButton = new QPushButton(centralWidget);
        LoadButton->setObjectName(QStringLiteral("LoadButton"));
        QFont font;
        font.setPointSize(12);
        LoadButton->setFont(font);
        LoadButton->setIconSize(QSize(20, 20));

        verticalLayout_3->addWidget(LoadButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(label);

        channel_combo_box = new QComboBox(centralWidget);
        channel_combo_box->setObjectName(QStringLiteral("channel_combo_box"));

        horizontalLayout_3->addWidget(channel_combo_box);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        CommentsLbl = new QLabel(centralWidget);
        CommentsLbl->setObjectName(QStringLiteral("CommentsLbl"));
        sizePolicy.setHeightForWidth(CommentsLbl->sizePolicy().hasHeightForWidth());
        CommentsLbl->setSizePolicy(sizePolicy);
        CommentsLbl->setMaximumSize(QSize(150, 20));

        verticalLayout_5->addWidget(CommentsLbl);

        ChannelComments = new QTextEdit(centralWidget);
        ChannelComments->setObjectName(QStringLiteral("ChannelComments"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ChannelComments->sizePolicy().hasHeightForWidth());
        ChannelComments->setSizePolicy(sizePolicy1);
        ChannelComments->setMinimumSize(QSize(600, 50));
        ChannelComments->setMaximumSize(QSize(600, 80));

        verticalLayout_5->addWidget(ChannelComments);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout->addLayout(horizontalLayout);

        signalPlot = new QCustomPlot(centralWidget);
        signalPlot->setObjectName(QStringLiteral("signalPlot"));

        verticalLayout->addWidget(signalPlot);

        fourierPlot = new QCustomPlot(centralWidget);
        fourierPlot->setObjectName(QStringLiteral("fourierPlot"));

        verticalLayout->addWidget(fourierPlot);


        verticalLayout_2->addLayout(verticalLayout);

        VibraPlotterClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(VibraPlotterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setToolTipDuration(-5);
        VibraPlotterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VibraPlotterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VibraPlotterClass->setStatusBar(statusBar);

        mainToolBar->addAction(actionNewProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLoadProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSaveProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSettings);

        retranslateUi(VibraPlotterClass);

        QMetaObject::connectSlotsByName(VibraPlotterClass);
    } // setupUi

    void retranslateUi(QMainWindow *VibraPlotterClass)
    {
        VibraPlotterClass->setWindowTitle(QApplication::translate("VibraPlotterClass", "VibraPlotter", 0));
        actionNewProject->setText(QApplication::translate("VibraPlotterClass", "NewProject", 0));
        actionNewProject->setShortcut(QApplication::translate("VibraPlotterClass", "Ctrl+N", 0));
        actionLoadProject->setText(QApplication::translate("VibraPlotterClass", "LoadProject", 0));
        actionSettings->setText(QApplication::translate("VibraPlotterClass", "Settings", 0));
        actionSaveProject->setText(QApplication::translate("VibraPlotterClass", "SaveProject", 0));
#ifndef QT_NO_TOOLTIP
        actionSaveProject->setToolTip(QApplication::translate("VibraPlotterClass", "Save Project", 0));
#endif // QT_NO_TOOLTIP
        LoadButton->setText(QApplication::translate("VibraPlotterClass", "Load Data", 0));
        label->setText(QApplication::translate("VibraPlotterClass", "Channel", 0));
        channel_combo_box->clear();
        channel_combo_box->insertItems(0, QStringList()
         << QApplication::translate("VibraPlotterClass", "1", 0)
         << QApplication::translate("VibraPlotterClass", "2", 0)
         << QApplication::translate("VibraPlotterClass", "3", 0)
         << QApplication::translate("VibraPlotterClass", "4", 0)
         << QApplication::translate("VibraPlotterClass", "5", 0)
         << QApplication::translate("VibraPlotterClass", "6", 0)
         << QApplication::translate("VibraPlotterClass", "7", 0)
        );
        CommentsLbl->setText(QApplication::translate("VibraPlotterClass", "Comments for Channel 1:", 0));
    } // retranslateUi

};

namespace Ui {
    class VibraPlotterClass: public Ui_VibraPlotterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIBRAPLOTTER_H
