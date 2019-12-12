#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    emu = new Emulator();
    emu->SetupConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Btn_Random_clicked()
{
    emu->FillActRandom();
}

void MainWindow::on_Btn_AppNode_clicked()
{
    emu->serv->setDnsNode(qPrintable(ui->lE1_node->text()));
}

void MainWindow::on_Btn2_AppName_clicked()
{
    emu->serv->serverName = ui->lE2_name->text();
}

void MainWindow::on_Btn_Start_clicked()
{
    if((ui->Btn_AppNode->isChecked()) && (ui->Btn2_AppName->isChecked())) {
        emu->serv->OpenOutFile();
        emu->serv->Npms = static_cast<quint8>(ui->SpinBox_Npms->value());
//        emu->serv->setNChannels(static_cast<quint8>(ui->SpinBox_Nchs->value()));
        emu->serv->startServer();
        ui->Btn_AppNode->setEnabled(0);
        ui->Btn2_AppName->setEnabled(0);
        ui->Btn_Start->setEnabled(0);
        ui->SpinBox_Npms->setEnabled(0);
//        ui->SpinBox_Nchs->setEnabled(0);

        ui->Btn_Random->setEnabled(1);
        ui->Btn_Stop->setEnabled(1);

        ui->lE1_node->setReadOnly(1);
        ui->lE2_name->setReadOnly(1);
    }
    else {
        QMessageBox::question(this, "Message", "Please apply 'DNS node' and 'Server name'",QMessageBox::Ok);
    }
}

void MainWindow::on_Btn_Stop_clicked()
{
    emu->serv->stopServer();
    emu->serv->CloseOutFile();

    ui->Btn_AppNode->setEnabled(1);     ui->Btn_AppNode->setChecked(0);
    ui->Btn2_AppName->setEnabled(1);    ui->Btn2_AppName->setChecked(0);
    ui->Btn_Start->setEnabled(1);
    ui->SpinBox_Npms->setEnabled(1);
//    ui->SpinBox_Nchs->setEnabled(1);

    ui->lE1_node->setReadOnly(0);
    ui->lE2_name->setReadOnly(0);

    ui->Btn_Random->setEnabled(0);
    ui->Btn_Stop->setEnabled(0);
}
