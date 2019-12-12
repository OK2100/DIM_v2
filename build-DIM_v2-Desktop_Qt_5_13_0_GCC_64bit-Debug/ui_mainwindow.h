/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lE1_node;
    QPushButton *Btn_Start;
    QLabel *lbl3;
    QPushButton *Btn_Random;
    QLineEdit *lE2_name;
    QPushButton *Btn2_AppName;
    QLabel *lbl2;
    QPushButton *Btn_AppNode;
    QLabel *lbl1;
    QSpinBox *SpinBox_Npms;
    QPushButton *Btn_Stop;
    QLabel *lbl3_2;
    QSpinBox *SpinBox_Nchs;
    QLabel *lbl3_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(450, 246);
        MainWindow->setMinimumSize(QSize(450, 200));
        MainWindow->setMaximumSize(QSize(450, 246));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lE1_node = new QLineEdit(centralwidget);
        lE1_node->setObjectName(QString::fromUtf8("lE1_node"));

        gridLayout_2->addWidget(lE1_node, 0, 1, 1, 1);

        Btn_Start = new QPushButton(centralwidget);
        Btn_Start->setObjectName(QString::fromUtf8("Btn_Start"));
        Btn_Start->setEnabled(true);

        gridLayout_2->addWidget(Btn_Start, 4, 1, 1, 1);

        lbl3 = new QLabel(centralwidget);
        lbl3->setObjectName(QString::fromUtf8("lbl3"));

        gridLayout_2->addWidget(lbl3, 2, 0, 1, 1);

        Btn_Random = new QPushButton(centralwidget);
        Btn_Random->setObjectName(QString::fromUtf8("Btn_Random"));
        Btn_Random->setEnabled(false);

        gridLayout_2->addWidget(Btn_Random, 4, 0, 1, 1);

        lE2_name = new QLineEdit(centralwidget);
        lE2_name->setObjectName(QString::fromUtf8("lE2_name"));

        gridLayout_2->addWidget(lE2_name, 1, 1, 1, 1);

        Btn2_AppName = new QPushButton(centralwidget);
        Btn2_AppName->setObjectName(QString::fromUtf8("Btn2_AppName"));
        Btn2_AppName->setCheckable(true);

        gridLayout_2->addWidget(Btn2_AppName, 1, 2, 1, 1);

        lbl2 = new QLabel(centralwidget);
        lbl2->setObjectName(QString::fromUtf8("lbl2"));

        gridLayout_2->addWidget(lbl2, 1, 0, 1, 1);

        Btn_AppNode = new QPushButton(centralwidget);
        Btn_AppNode->setObjectName(QString::fromUtf8("Btn_AppNode"));
        Btn_AppNode->setCheckable(true);

        gridLayout_2->addWidget(Btn_AppNode, 0, 2, 1, 1);

        lbl1 = new QLabel(centralwidget);
        lbl1->setObjectName(QString::fromUtf8("lbl1"));

        gridLayout_2->addWidget(lbl1, 0, 0, 1, 1);

        SpinBox_Npms = new QSpinBox(centralwidget);
        SpinBox_Npms->setObjectName(QString::fromUtf8("SpinBox_Npms"));
        SpinBox_Npms->setMinimum(1);
        SpinBox_Npms->setMaximum(20);
        SpinBox_Npms->setValue(1);
        SpinBox_Npms->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(SpinBox_Npms, 2, 1, 1, 1);

        Btn_Stop = new QPushButton(centralwidget);
        Btn_Stop->setObjectName(QString::fromUtf8("Btn_Stop"));
        Btn_Stop->setEnabled(false);

        gridLayout_2->addWidget(Btn_Stop, 4, 2, 1, 1);

        lbl3_2 = new QLabel(centralwidget);
        lbl3_2->setObjectName(QString::fromUtf8("lbl3_2"));
        lbl3_2->setEnabled(false);

        gridLayout_2->addWidget(lbl3_2, 3, 0, 1, 1);

        SpinBox_Nchs = new QSpinBox(centralwidget);
        SpinBox_Nchs->setObjectName(QString::fromUtf8("SpinBox_Nchs"));
        SpinBox_Nchs->setEnabled(false);
        SpinBox_Nchs->setMinimum(1);
        SpinBox_Nchs->setMaximum(12);
        SpinBox_Nchs->setValue(1);
        SpinBox_Nchs->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(SpinBox_Nchs, 3, 1, 1, 1);

        lbl3_3 = new QLabel(centralwidget);
        lbl3_3->setObjectName(QString::fromUtf8("lbl3_3"));
        lbl3_3->setEnabled(false);

        gridLayout_2->addWidget(lbl3_3, 3, 2, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 1);

        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 450, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lE1_node->setText(QCoreApplication::translate("MainWindow", "hplu-Notebook-PC", nullptr));
        Btn_Start->setText(QCoreApplication::translate("MainWindow", "Start server", nullptr));
        lbl3->setText(QCoreApplication::translate("MainWindow", "Number of PMs:", nullptr));
        Btn_Random->setText(QCoreApplication::translate("MainWindow", "Randomize ACT", nullptr));
        lE2_name->setText(QCoreApplication::translate("MainWindow", "FIT_DIM_server", nullptr));
        Btn2_AppName->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        lbl2->setText(QCoreApplication::translate("MainWindow", "Set Server name:", nullptr));
        Btn_AppNode->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        lbl1->setText(QCoreApplication::translate("MainWindow", "Set DNS node:", nullptr));
        Btn_Stop->setText(QCoreApplication::translate("MainWindow", "Stop server", nullptr));
        lbl3_2->setText(QCoreApplication::translate("MainWindow", " Channels in PM:", nullptr));
        lbl3_3->setText(QCoreApplication::translate("MainWindow", "Doesn't work yet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
