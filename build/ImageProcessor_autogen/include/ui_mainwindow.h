/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *before;
    QPushButton *pushButton_20;
    QPushButton *pushButton;
    QPushButton *UndoButton;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QLabel *after;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 900);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(181, 181, 181, 179));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(206, 206, 206, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ffffff;\n"
"    color: #2e3440;\n"
"    border-radius: 5px;\n"
"    border: 1px solid #d8dee9;\n"
"    font-weight: bold;\n"
"    min-width: 130px;    \n"
"    max-width: 130px;\n"
"    min-height: 30px; \n"
"    max-height: 30px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #eceff4;\n"
"    border-color: #5e81ac;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e5e9f0;\n"
"}\n"
"\n"
"QPushButton#loadbtn, QPushButton#savebtn {\n"
"    background-color: #ffffff;\n"
"    color: #2e3440;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    border-radius: 7px;\n"
"    border: 2px solid #5e81ac;\n"
"    min-width: 170px;  \n"
"    max-width: 170px;\n"
"    min-height: 36px;   \n"
"    max-height: 36px;\n"
"}\n"
"\n"
"QPushButton#loadbtn:hover, QPushButton#savebtn:hover {\n"
"    background-color: #f0f4f8;\n"
"    border-color: #81a1c1;\n"
"}\n"
"\n"
"QPushButton#loadbtn:pressed, QPushButton#savebtn:pressed {\n"
"    background-color: #e2"
                        "e8f0;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #4a90d9;\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"    color: #222;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #e8f2ff;\n"
"    border: 2px solid #1c6fd1;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4a90d9;\n"
"    color: white;\n"
"    border: 3px solid #14529c;\n"
"    padding-top: 8px;\n"
"    padding-left: 8px;\n"
"}"));
        before = new QLabel(centralwidget);
        before->setObjectName("before");
        before->setGeometry(QRect(270, 150, 271, 301));
        pushButton_20 = new QPushButton(centralwidget);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(820, 540, 146, 46));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(270, 20, 150, 46));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(140);
        sizePolicy1.setVerticalStretch(140);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    text-align: right;\n"
"    padding-right: 10px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Images/images.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(24, 24));
        UndoButton = new QPushButton(centralwidget);
        UndoButton->setObjectName("UndoButton");
        UndoButton->setGeometry(QRect(820, 10, 146, 46));
        scrollArea_2 = new QScrollArea(centralwidget);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(20, 10, 171, 671));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea_2->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 219, 909));
        pushButton_2 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 0, 146, 46));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(140);
        sizePolicy2.setVerticalStretch(140);
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);
        pushButton_2->setMinimumSize(QSize(146, 46));
        pushButton_2->setMaximumSize(QSize(146, 46));
        pushButton_3 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 50, 146, 46));
        pushButton_4 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 100, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy2);
        pushButton_4->setMinimumSize(QSize(146, 46));
        pushButton_4->setMaximumSize(QSize(146, 46));
        pushButton_5 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 150, 146, 46));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMinimumSize(QSize(146, 46));
        pushButton_5->setMaximumSize(QSize(146, 46));
        pushButton_6 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 200, 146, 46));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMinimumSize(QSize(146, 46));
        pushButton_6->setMaximumSize(QSize(146, 46));
        pushButton_7 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 250, 146, 46));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMinimumSize(QSize(146, 46));
        pushButton_7->setMaximumSize(QSize(146, 46));
        pushButton_8 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 300, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy2);
        pushButton_8->setMinimumSize(QSize(146, 46));
        pushButton_8->setMaximumSize(QSize(146, 46));
        pushButton_9 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 350, 146, 46));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMinimumSize(QSize(146, 46));
        pushButton_9->setMaximumSize(QSize(146, 46));
        pushButton_10 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(10, 400, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy2);
        pushButton_10->setMinimumSize(QSize(146, 46));
        pushButton_10->setMaximumSize(QSize(146, 46));
        pushButton_11 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(10, 450, 146, 46));
        sizePolicy1.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy1);
        pushButton_12 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(10, 500, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy2);
        pushButton_12->setMinimumSize(QSize(146, 46));
        pushButton_12->setMaximumSize(QSize(146, 46));
        pushButton_13 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(10, 550, 146, 46));
        sizePolicy1.setHeightForWidth(pushButton_13->sizePolicy().hasHeightForWidth());
        pushButton_13->setSizePolicy(sizePolicy1);
        pushButton_14 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(10, 600, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_14->sizePolicy().hasHeightForWidth());
        pushButton_14->setSizePolicy(sizePolicy2);
        pushButton_14->setMinimumSize(QSize(146, 46));
        pushButton_14->setMaximumSize(QSize(146, 46));
        pushButton_15 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(10, 650, 146, 46));
        pushButton_16 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(10, 700, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_16->sizePolicy().hasHeightForWidth());
        pushButton_16->setSizePolicy(sizePolicy2);
        pushButton_16->setMinimumSize(QSize(146, 46));
        pushButton_16->setMaximumSize(QSize(146, 46));
        pushButton_17 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(10, 750, 146, 46));
        pushButton_18 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(10, 800, 146, 46));
        sizePolicy2.setHeightForWidth(pushButton_18->sizePolicy().hasHeightForWidth());
        pushButton_18->setSizePolicy(sizePolicy2);
        pushButton_18->setMinimumSize(QSize(146, 46));
        pushButton_18->setMaximumSize(QSize(146, 46));
        pushButton_19 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(10, 850, 146, 46));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        after = new QLabel(centralwidget);
        after->setObjectName("after");
        after->setGeometry(QRect(620, 150, 321, 301));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        before->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "savebtn", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "loadbtn", nullptr));
        UndoButton->setText(QCoreApplication::translate("MainWindow", "undobtn", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "greyscale ", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "black and white", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "invert", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "frame", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "flip", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "rotate", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "darken&lighten", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "resize", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "merge", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "detect image", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "crop image", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "blur", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "sunlight", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "old tv", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "purple", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "infrared", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "skew", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "oil painting", nullptr));
        after->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
