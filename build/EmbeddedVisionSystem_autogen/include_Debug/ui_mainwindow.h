/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *videoLabel;
    QHBoxLayout *controlLayout;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *resetButton;
    QPushButton *snapshotButton;
    QLabel *frameRateLabel;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videoLabel = new QLabel(centralwidget);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoLabel->sizePolicy().hasHeightForWidth());
        videoLabel->setSizePolicy(sizePolicy);
        videoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(videoLabel);

        controlLayout = new QHBoxLayout();
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));

        controlLayout->addWidget(playButton);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        controlLayout->addWidget(pauseButton);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        controlLayout->addWidget(resetButton);

        snapshotButton = new QPushButton(centralwidget);
        snapshotButton->setObjectName(QString::fromUtf8("snapshotButton"));

        controlLayout->addWidget(snapshotButton);


        verticalLayout->addLayout(controlLayout);

        frameRateLabel = new QLabel(centralwidget);
        frameRateLabel->setObjectName(QString::fromUtf8("frameRateLabel"));

        verticalLayout->addWidget(frameRateLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        snapshotButton->setText(QCoreApplication::translate("MainWindow", "Save Snapshot", nullptr));
        frameRateLabel->setText(QCoreApplication::translate("MainWindow", "Frame Rate: 0 FPS", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
