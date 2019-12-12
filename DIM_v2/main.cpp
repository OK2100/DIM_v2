#include "mainwindow.h"
//#include "mydimserver.h"
//#include "emulator.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    MyDimServer* serv;
//    QString node;
//    node = "hplu-Notebook-PC";
//    serv = new MyDimServer(node);
//    serv->startServer();



//    QObject::connect(serv,&MyDimServer::set_ADC_ZERO_requested,serv,&MyDimServer::test_slot3);
//    QObject::connect(serv,&MyDimServer::set_ADC_DELAY_requested,serv,&MyDimServer::test_slot3);
//    QObject::connect(serv,&MyDimServer::set_CFD_TRESHOLD_requested,serv,&MyDimServer::test_slot3);
//    QObject::connect(serv,&MyDimServer::set_CFD_ZERO_requested,serv,&MyDimServer::test_slot3);
//    QObject::connect(serv,&MyDimServer::apply_ADC_ZERO_requested,serv,&MyDimServer::test_slot1);
//    QObject::connect(serv,&MyDimServer::apply_CH_MASK_requested,serv,&MyDimServer::test_slot0);
//    QObject::connect(serv,&MyDimServer::set_OR_GATE_requested,serv,&MyDimServer::test_slot);
//    QObject::connect(serv,&MyDimServer::set_CFD_SATR_requested,serv,&MyDimServer::test_slot);
//    QObject::connect(serv,&MyDimServer::set_RDH_PAR_requested,serv,&MyDimServer::test_slot);

//    QObject::connect(serv,&MyDimServer::set_TRESHOLD_CALIBR_requested,serv,&MyDimServer::update_new_TRESHOLD_CALIBR);



    return a.exec();
}
