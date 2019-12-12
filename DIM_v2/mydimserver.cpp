#include "mydimserver.h"


pm_pNonValSignal getPMNonValPointerToSignal(QString PARname){ return PMNonValHash[PARname]; };
pmch_pNonValSignal getPMCHNonValPointerToSignal(QString PARname){ return PMCHNonValHash[PARname]; };




//  ==========================================  MyDimServer  =============================================

MyDimServer::MyDimServer(QString dns_node,QString server_name)  :
    QObject(nullptr)//,
{
    dnsNode = dns_node;
    serverName = server_name;
    setDnsNode(qPrintable(dnsNode));

    fillPMValHash();
    fillPMCHValHash();
    fillPMNonValHash();
    fillPMCHNonValHash();
}

MyDimServer::~MyDimServer()
{
    for(quint8 i=0;i<Npms;i++){
        delete pm[i];
    }
    PMValHash<quint8>.clear();      PMValHash<quint16>.clear();     PMValHash<quint32>.clear();
    PMValHash<qint8>.clear();       PMValHash<qint16>.clear();      PMValHash<qint32>.clear();
    PMCHValHash<quint8>.clear();    PMCHValHash<quint16>.clear();   PMCHValHash<quint32>.clear();
    PMCHValHash<qint8>.clear();     PMCHValHash<qint16>.clear();    PMCHValHash<qint32>.clear();
    PMNonValHash.clear();
    PMCHNonValHash.clear();
}

void MyDimServer::startServer()
{
    setDnsNode(qPrintable(dnsNode));
    start(qPrintable(serverName));
     cout << "###################################################" << endl
          << "Start DIM server on " << dnsNode << endl
          << "###################################################" << endl;

     for(quint8 i=0;i<Npms;i++) {
         pm[i] = new PMPars(this);
         pm[i]->PMid = i+1;
         pm[i]->publish();
     }
}

void MyDimServer::stopServer()
{
    this->stop();
    cout << "###################################################" << endl
         << "Stop DIM server "  << endl
         << "###################################################" << endl;
}

void MyDimServer::OpenOutFile()
{
    DimServicesFile.open(QIODevice::WriteOnly);
    DimCommandsFile.open(QIODevice::WriteOnly);
}

void MyDimServer::CloseOutFile()
{
    DimServicesFile.close();
    DimCommandsFile.close();
}

void MyDimServer::setNChannels(quint8 nch)      // Doesn't work yet
{
    for(quint8 i=0;i<Npms;i++){
        pm[i]->Nchannels = nch;
//        cout << pm[i]->Nchannels <<endl;
    }
}

template<class Y>
void MyDimServer::emitSignal(pmch_pValSignal<Y> pSignal,quint8 PMid,quint8 Chid, Y val)
{
   if(pSignal != nullptr)
   emit (this->*pSignal)(PMid,Chid,val);
}

void MyDimServer::emitSignal(pmch_pNonValSignal pSignal, quint8 PMid, quint8 Chid)
{
   if(pSignal != nullptr)
   emit (this->*pSignal)(PMid,Chid);
}

template<class Y>
void MyDimServer::emitSignal(pm_pValSignal<Y> pSignal,quint8 PMid, Y val)
{
    if(pSignal != nullptr)
    emit (this->*pSignal)(PMid,val);
}

void MyDimServer::emitSignal(pm_pNonValSignal pSignal, quint8 PMid)
{
   if(pSignal != nullptr)
   emit (this->*pSignal)(PMid);
}

//  ===================================================================================================

//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PMPars @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PMPars::PMPars(MyDimServer* _server):
            PMid(0)
{
//    cout << "PMPARS" << Nchannels << endl;

    adczero.resize(Nchannels);
    adcdelay.resize(Nchannels);
    adc0offset.resize(Nchannels);
    adc1offset.resize(Nchannels);
    adc0range.resize(Nchannels);
    adc1range.resize(Nchannels);
    timealign.resize(Nchannels);
    cfdthreshold.resize(Nchannels);
    cfdzero.resize(Nchannels);
    thresholdcalibr.resize(Nchannels);
    alltoch.resize(Nchannels);

    adc0meanampl.resize(Nchannels);
    adc1meanampl.resize(Nchannels);
    adc0zerolvl.resize(Nchannels);
    adc1zerolvl.resize(Nchannels);
    cfdcnt.resize(Nchannels);
    trgcnt.resize(Nchannels);
    rawtdcdata.resize(Nchannels);

    for( quint8 i=0; i<Nchannels; i++){
        adczero[i]          = new PMCHfullPar<qint16>("ADC_ZERO",_server);
        adcdelay[i]         = new PMCHfullPar<qint16>("ADC_DELAY",_server);
        adc0offset[i]       = new PMCHfullPar<quint16>("ADC0_OFFSET",_server);
        adc1offset[i]       = new PMCHfullPar<quint16>("ADC1_OFFSET",_server);
        adc0range[i]        = new PMCHfullPar<quint16>("ADC0_RANGE",_server);
        adc1range[i]        = new PMCHfullPar<quint16>("ADC1_RANGE",_server);
        timealign[i]        = new PMCHfullPar<quint16>("TIME_ALIGN",_server);
        cfdthreshold[i]     = new PMCHfullPar<qint16>("CFD_THRESHOLD",_server);
        cfdzero[i]          = new PMCHfullPar<qint16>("CFD_ZERO",_server);
        thresholdcalibr[i]  = new PMCHfullPar<qint16>("THRESHOLD_CALIBR",_server);
        alltoch[i]          = new PMCHonlyAppPar("ALLtoCh",_server);

        adc0meanampl[i]     = new  PMCHonlyActPar<quint16>("ADC0_MEANAMPL",_server);
        adc1meanampl[i]     = new  PMCHonlyActPar<quint16>("ADC1_MEANAMPL",_server);
        adc0zerolvl[i]      = new  PMCHonlyActPar<quint16>("ADC0_ZEROLVL",_server);
        adc1zerolvl[i]      = new  PMCHonlyActPar<quint16>("ADC1_ZEROLVL",_server);
        cfdcnt[i]           = new  PMCHonlyActPar<quint32>("CFD_CNT",_server);
        trgcnt[i]           = new  PMCHonlyActPar<quint32>("TRG_CNT",_server);
        rawtdcdata[i]       = new  PMCHonlyActPar<quint16>("RAW_TDC_DATA",_server);
    }

    chmask              = new PMfullPar<quint16>("CH_MASK",_server);    chmask->prefix = "/control";
    cfdsatr             = new PMfullPar<quint16>("CFD_SATR",_server);   cfdsatr->prefix = "/control";
    orgate              = new PMfullPar<quint8>("OR_GATE",_server);     orgate->prefix = "/control";

    resetcounters       = new PMonlyAppPar("RESET_COUNTERS",_server);       resetcounters->prefix = "/control";
    zerolvlcalibration  = new PMonlyAppPar("ZERO_LVL_CALIBR",_server);      zerolvlcalibration->prefix = "/control";
    resetorbitsync      = new PMonlyAppPar("RESET_ORBIT_SYNC",_server);
    resetdrophitcnts    = new PMonlyAppPar("RESET_DROPPING_HIT_COUNTERS",_server);
    resetgenbunchoffset = new PMonlyAppPar("RESET_GEN_BUNCH_OFFSET",_server);
    resetgbterrors      = new PMonlyAppPar("RESET_GBT_ERRORS",_server);
    resetgbt            = new PMonlyAppPar("RESET_GBT",_server);
    resetrxphaseerror   = new PMonlyAppPar("RESET_RX_PHASE_ERROR",_server);
    sendreadoutcommand  = new PMonlyValAppPar<quint8>("SEND_READOUT_COMMAND",_server);


    tgmode              = new PMActnValAppPar<quint8>("TG_MODE",_server);
    tgpattern1          = new PMfullPar<quint32>("TG_PATTERN_1",_server);
    tgpattern0          = new PMfullPar<quint32>("TG_PATTERN_0",_server);
    tgcontvalue         = new PMfullPar<quint8>("TG_CONT_VALUE",_server);
    tgsendsingle        = new PMonlyValAppPar<quint32>("TG_SEND_SINGLE",_server);
    tgbunchfreq         = new PMfullPar<quint16>("TG_BUNCH_FREQ",_server);
    tgfreqoffset        = new PMfullPar<quint16>("TG_FREQ_OFFSET",_server);
    dgmode              = new PMActnValAppPar<quint8>("DG_MODE",_server);
    dgtrgrespondmask    = new PMfullPar<quint32>("DG_TRG_RESPOND_MASK",_server);
    dgbunchpattern      = new PMfullPar<quint32>("DG_BUNCH_PATTERN",_server);
    dgbunchfreq         = new PMfullPar<quint16>("DG_BUNCH_FREQ",_server);
    dgfreqoffset        = new PMfullPar<quint16>("DG_FREQ_OFFSET",_server);
    rdhfeeid            = new PMfullPar<quint16>("RDH_FEE_ID",_server);
    rdhpar              = new PMfullPar<quint16>("RDH_PAR",_server);
    rdhmaxpayload       = new PMfullPar<quint16>("RDH_MAX_PAYLOAD",_server);
    rdhdetfield         = new PMfullPar<quint16>("RDH_DET_FIELD",_server);
    crutrgcomparedelay  = new PMfullPar<quint16>("CRU_TRG_COMPARE_DELAY",_server);
    bciddelay           = new PMfullPar<quint16>("BCID_DELAY",_server);
    alltopm             = new PMonlyAppPar("ALLtoPM",_server);                  alltopm->prefix = "/control";

    boardstatus         = new PMonlyActPar<quint16>("BOARD_STATUS",_server);    boardstatus->prefix = "/status";
    temperature         = new PMonlyActPar<quint16>("TEMPERATURE",_server);     temperature->prefix = "/status";
    hdmilink            = new PMonlyActPar<quint32>("HDMI_LINK",_server);       hdmilink->prefix = "/status";
    bits                = new PMonlyActPar<quint16>("BITS",_server);
    readoutmode         = new PMonlyActPar<quint8>("READOUT_MODE",_server);
    bcidsyncmode        = new PMonlyActPar<quint8>("BCID_SYNC_MODE",_server);
    rxphase             = new PMonlyActPar<quint8>("RX_PHASE",_server);
    cruorbit            = new PMonlyActPar<quint32>("CRU_ORBIT",_server);
    crubc               = new PMonlyActPar<quint16>("CRU_BC",_server);
    rawfifo             = new PMonlyActPar<quint16>("RAW_FIFO",_server);
    selfifo             = new PMonlyActPar<quint16>("SEL_FIFO",_server);
    selfirsthit         = new PMonlyActPar<quint32>("SEL_FIRST_HIT_DROPPED_ORBIT",_server);
    sellasthit          = new PMonlyActPar<quint16>("SEL_LAST_HIT_DROPPED_ORBIT",_server);
    selhitsdropped      = new PMonlyActPar<quint16>("SEL_HITS_DROPPED",_server);
    readoutrate         = new PMonlyActPar<quint16>("READOUT_RATE",_server);

    pServer = _server;
}

PMPars::~PMPars()
{
    for( quint8 i=0; i<Nchannels; i++){
        delete adczero[i];
        delete adcdelay[i];
        delete adc0offset[i];
        delete adc1offset[i];
        delete adc0range[i];
        delete adc1range[i];
        delete timealign[i];
        delete cfdthreshold[i];
        delete cfdzero[i];
        delete thresholdcalibr[i];
        delete alltoch[i];

        delete adc0meanampl[i];
        delete adc1meanampl[i];
        delete adc0zerolvl[i];
        delete adc1zerolvl[i];
        delete cfdcnt[i];
        delete trgcnt[i];
        delete rawtdcdata[i];
    }

    delete chmask;
    delete cfdsatr;
    delete orgate;
    delete resetcounters;
    delete zerolvlcalibration;

    delete resetorbitsync;
    delete resetdrophitcnts;
    delete resetgenbunchoffset;
    delete resetgbterrors;
    delete resetgbt;
    delete resetrxphaseerror;
    delete sendreadoutcommand;
    delete  tgmode;
    delete tgpattern1;
    delete tgpattern0;
    delete  tgcontvalue;
    delete tgsendsingle;
    delete tgbunchfreq;
    delete tgfreqoffset;
    delete dgmode;
    delete dgtrgrespondmask;
    delete dgbunchpattern;
    delete dgbunchfreq;
    delete dgfreqoffset;
    delete rdhfeeid;
    delete rdhpar;
    delete rdhmaxpayload;
    delete rdhdetfield;
    delete crutrgcomparedelay;
    delete bciddelay;
    delete alltopm;

    delete boardstatus;
    delete temperature;
    delete hdmilink;
    delete bits;
    delete readoutmode;
    delete bcidsyncmode;
    delete rxphase;
    delete cruorbit;
    delete crubc;
    delete rawfifo;
    delete selfifo;
    delete selfirsthit;
    delete sellasthit;
    delete selhitsdropped;
    delete readoutrate;

}

void PMPars::publish()
{
        //  loop for channels
        for(quint8 i=0; i<Nchannels; i++) {

            adczero[i]->SetCHid(i+1);        adczero[i]->SetPMid(PMid);       adczero[i]->publishCommands();        adczero[i]->publishServices();
            adcdelay[i]->SetCHid(i+1);       adcdelay[i]->SetPMid(PMid);      adcdelay[i]->publishCommands();       adcdelay[i]->publishServices();
            adc0offset[i]->SetCHid(i+1);     adc0offset[i]->SetPMid(PMid);    adc0offset[i]->publishCommands();     adc0offset[i]->publishServices();
            adc1offset[i]->SetCHid(i+1);     adc1offset[i]->SetPMid(PMid);    adc1offset[i]->publishCommands();     adc1offset[i]->publishServices();
            adc0range[i]->SetCHid(i+1);      adc0range[i]->SetPMid(PMid);     adc0range[i]->publishCommands();      adc0range[i]->publishServices();
            adc1range[i]->SetCHid(i+1);      adc1range[i]->SetPMid(PMid);     adc1range[i]->publishCommands();      adc1range[i]->publishServices();
            timealign[i]->SetCHid(i+1);       timealign[i]->SetPMid(PMid);      timealign[i]->publishCommands();       timealign[i]->publishServices();
            cfdthreshold[i]->SetCHid(i+1);    cfdthreshold[i]->SetPMid(PMid);   cfdthreshold[i]->publishCommands();    cfdthreshold[i]->publishServices();
            cfdzero[i]->SetCHid(i+1);        cfdzero[i]->SetPMid(PMid);       cfdzero[i]->publishCommands();        cfdzero[i]->publishServices();
            thresholdcalibr[i]->SetCHid(i+1); thresholdcalibr[i]->SetPMid(PMid);thresholdcalibr[i]->publishCommands(); thresholdcalibr[i]->publishServices();

            alltoch[i]->SetCHid(i+1);        alltoch[i]->SetPMid(PMid);       alltoch[i]->publishCommands();

            adc0meanampl[i]->SetCHid(i+1);   adc0meanampl[i]->SetPMid(PMid);                                      adc0meanampl[i]->publishServices();
            adc1meanampl[i]->SetCHid(i+1);   adc1meanampl[i]->SetPMid(PMid);                                      adc1meanampl[i]->publishServices();
            adc0zerolvl[i]->SetCHid(i+1);    adc0zerolvl[i]->SetPMid(PMid);                                       adc0zerolvl[i]->publishServices();
            adc1zerolvl[i]->SetCHid(i+1);    adc1zerolvl[i]->SetPMid(PMid);                                       adc1zerolvl[i]->publishServices();
            cfdcnt[i]->SetCHid(i+1);         cfdcnt[i]->SetPMid(PMid);                                            cfdcnt[i]->publishServices();
            trgcnt[i]->SetCHid(i+1);         trgcnt[i]->SetPMid(PMid);                                            trgcnt[i]->publishServices();
            rawtdcdata[i]->SetCHid(i+1);     rawtdcdata[i]->SetPMid(PMid);                                        rawtdcdata[i]->publishServices();

        }

        chmask->SetPMid(PMid);                   chmask->publishCommands();                    chmask->publishServices();
        cfdsatr->SetPMid(PMid);                  cfdsatr->publishCommands();                   cfdsatr->publishServices();
        orgate->SetPMid(PMid);                   orgate->publishCommands();                    orgate->publishServices();
        resetcounters->SetPMid(PMid);            resetcounters->publishCommands();
        zerolvlcalibration->SetPMid(PMid);       zerolvlcalibration->publishCommands();

        resetorbitsync->SetPMid(PMid);           resetorbitsync->publishCommands();
        resetdrophitcnts->SetPMid(PMid);         resetdrophitcnts->publishCommands();
        resetgenbunchoffset->SetPMid(PMid);      resetgenbunchoffset->publishCommands();
        resetgbterrors->SetPMid(PMid);           resetgbterrors->publishCommands();
        resetgbt->SetPMid(PMid);                 resetgbt->publishCommands();
        resetrxphaseerror->SetPMid(PMid);        resetrxphaseerror->publishCommands();
        sendreadoutcommand->SetPMid(PMid);       sendreadoutcommand->publishCommands();
        tgmode->SetPMid(PMid);                   tgmode->publishCommands();                    tgmode->publishServices();
        tgpattern1->SetPMid(PMid);               tgpattern1->publishCommands();                tgpattern1->publishServices();
        tgpattern0->SetPMid(PMid);               tgpattern0->publishCommands();                tgpattern0->publishServices();
        tgcontvalue->SetPMid(PMid);              tgcontvalue->publishCommands();               tgcontvalue->publishServices();
        tgsendsingle->SetPMid(PMid);             tgsendsingle->publishCommands();
        tgbunchfreq->SetPMid(PMid);              tgbunchfreq->publishCommands();               tgbunchfreq->publishServices();
        tgfreqoffset->SetPMid(PMid);             tgfreqoffset->publishCommands();              tgfreqoffset->publishServices();
        dgmode->SetPMid(PMid);                   dgmode->publishCommands();                    dgmode->publishServices();
        dgtrgrespondmask->SetPMid(PMid);         dgtrgrespondmask->publishCommands();          dgtrgrespondmask->publishServices();
        dgbunchpattern->SetPMid(PMid);           dgbunchpattern->publishCommands();            dgbunchpattern->publishServices();
        dgbunchfreq->SetPMid(PMid);              dgbunchfreq->publishCommands();               dgbunchfreq->publishServices();
        dgfreqoffset->SetPMid(PMid);             dgfreqoffset->publishCommands();              dgfreqoffset->publishServices();
        rdhfeeid->SetPMid(PMid);                 rdhfeeid->publishCommands();                  rdhfeeid->publishServices();
        rdhpar->SetPMid(PMid);                   rdhpar->publishCommands();                    rdhpar->publishServices();
        rdhmaxpayload->SetPMid(PMid);            rdhmaxpayload->publishCommands();             rdhmaxpayload->publishServices();
        rdhdetfield->SetPMid(PMid);              rdhdetfield->publishCommands();               rdhdetfield->publishServices();
        crutrgcomparedelay->SetPMid(PMid);       crutrgcomparedelay->publishCommands();        crutrgcomparedelay->publishServices();
        bciddelay->SetPMid(PMid);                bciddelay->publishCommands();                 bciddelay->publishServices();
        alltopm->SetPMid(PMid);                  alltopm->publishCommands();


        boardstatus->SetPMid(PMid);                                                          boardstatus->publishServices();
        temperature->SetPMid(PMid);                                                          temperature->publishServices();
        hdmilink->SetPMid(PMid);                                                             hdmilink->publishServices();
        bits->SetPMid(PMid);                                                                 bits->publishServices();
        readoutmode->SetPMid(PMid);                                                          readoutmode->publishServices();
        bcidsyncmode->SetPMid(PMid);                                                         bcidsyncmode->publishServices();
        rxphase->SetPMid(PMid);                                                              rxphase->publishServices();
        cruorbit->SetPMid(PMid);                                                             cruorbit->publishServices();
        crubc->SetPMid(PMid);                                                                crubc->publishServices();
        rawfifo->SetPMid(PMid);                                                              rawfifo->publishServices();
        selfifo->SetPMid(PMid);                                                              selfifo->publishServices();
        selfirsthit->SetPMid(PMid);                                                          selfirsthit->publishServices();
        sellasthit->SetPMid(PMid);                                                           sellasthit->publishServices();
        selhitsdropped->SetPMid(PMid);                                                       selhitsdropped->publishServices();
        readoutrate->SetPMid(PMid);                                                          readoutrate->publishServices();
}

//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void fillPMValHash()
{
    PMValHash<quint16>.insert("CH_MASK",                &MyDimServer::set_CH_MASK_requested);
    PMValHash<quint16>.insert("CFD_SATR",               &MyDimServer::set_CFD_SATR_requested);
    PMValHash<quint8>.insert("OR_GATE",                 &MyDimServer::set_OR_GATE_requested);
///////////////////////////////////////// PMSetHash<quint8>.insert("TG_MODE",                nullptr);
    PMValHash<quint32>.insert("TG_PATTERN_1",             &MyDimServer::set_TG_PATTERN_1_requested);
    PMValHash<quint32>.insert("TG_PATTERN_0",             &MyDimServer::set_TG_PATTERN_0_requested);
    PMValHash<quint8>.insert("TG_CONT_VALUE",           &MyDimServer::set_TG_CONT_VALUE_requested);
    PMValHash<quint16>.insert("TG_BUNCH_FREQ",          &MyDimServer::set_TG_BUNCH_FREQ_requested);
    PMValHash<quint16>.insert("TG_FREQ_OFFSET",         &MyDimServer::set_TG_FREQ_OFFSET_requested);
///////////////////////////////////////// PMValHash<quint16>.insert("DG_MODE",                nullptr);
    PMValHash<quint32>.insert("DG_TRG_RESPOND_MASK",    &MyDimServer::set_DG_TRG_RESPOND_MASK_requested);
    PMValHash<quint32>.insert("DG_BUNCH_PATTERN",       &MyDimServer::set_DG_BUNCH_PATTERN_requested);
    PMValHash<quint16>.insert("DG_BUNCH_FREQ",          &MyDimServer::set_DG_BUNCH_FREQ_requested);
    PMValHash<quint16>.insert("DG_FREQ_OFFSET",         &MyDimServer::set_DG_FREQ_OFFSET_requested);
    PMValHash<quint16>.insert("RDH_FEE_ID",             &MyDimServer::set_RDH_FEE_ID_requested);
    PMValHash<quint16>.insert("RDH_PAR",                &MyDimServer::set_RDH_PAR_requested);
    PMValHash<quint16>.insert("RDH_MAX_PAYLOAD",        &MyDimServer::set_RDH_MAX_PAYLOAD_requested);
    PMValHash<quint16>.insert("RDH_DET_FIELD",          &MyDimServer::set_RDH_DET_FIELD_requested);
    PMValHash<quint16>.insert("CRU_TRG_COMPARE_DELAY",  &MyDimServer::set_CRU_TRG_COMPARE_DELAY_requested);
    PMValHash<quint16>.insert("BCID_DELAY",             &MyDimServer::set_BCID_DELAY_requested);


    PMValHash<quint8>.insert("SEND_READOUT_COMMAND",    &MyDimServer::apply_SEND_READOUT_COMMAND_requested);
    PMValHash<quint32>.insert("TG_SEND_SINGLE",         &MyDimServer::apply_TG_SEND_SINGLE_requested);
    PMValHash<quint8>.insert("TG_MODE",                 &MyDimServer::apply_TG_MODE_requested);
    PMValHash<quint8>.insert("DG_MODE",                 &MyDimServer::apply_DG_MODE_requested);

};

void fillPMCHValHash()
{
    PMCHValHash<qint16>.insert("ADC_ZERO",    &MyDimServer::set_ADC_ZERO_requested);
    PMCHValHash<qint16>.insert("ADC_DELAY",   &MyDimServer::set_ADC_DELAY_requested);
    PMCHValHash<quint16>.insert("ADC0_OFFSET", &MyDimServer::set_ADC0_OFFSET_requested);
    PMCHValHash<quint16>.insert("ADC1_OFFSET", &MyDimServer::set_ADC1_OFFSET_requested);
    PMCHValHash<quint16>.insert("ADC0_RANGE",  &MyDimServer::set_ADC0_RANGE_requested);
    PMCHValHash<quint16>.insert("ADC1_RANGE",  &MyDimServer::set_ADC1_RANGE_requested);
    PMCHValHash<quint16>.insert("TIME_ALIGN",   &MyDimServer::set_TIME_ALIGN_requested);
    PMCHValHash<qint16>.insert("CFD_THRESHOLD",&MyDimServer::set_CFD_THRESHOLD_requested);
    PMCHValHash<qint16>.insert("CFD_ZERO",    &MyDimServer::set_CFD_ZERO_requested);
    PMCHValHash<qint16>.insert("THRESHOLD_CALIBR",&MyDimServer::set_THRESHOLD_CALIBR_requested);

}

void fillPMNonValHash()
{
    PMNonValHash.insert("CH_MASK",         &MyDimServer::apply_CH_MASK_requested);
    PMNonValHash.insert("CFD_SATR",        &MyDimServer::apply_CFD_SATR_requested);
    PMNonValHash.insert("OR_GATE",         &MyDimServer::apply_OR_GATE_requested);
    PMNonValHash.insert("RESET_COUNTERS",  &MyDimServer::apply_RESET_COUNTERS_requested);
    PMNonValHash.insert("ZERO_LVL_CALIBR", &MyDimServer::apply_ZERO_LVL_CALIBR_requested);

    PMNonValHash.insert("RESET_ORBIT_SYNC",            &MyDimServer::apply_RESET_ORBIT_SYNC_requested);
    PMNonValHash.insert("RESET_DROPPING_HIT_COUNTERS", &MyDimServer::apply_RESET_DROPPING_HIT_COUNTERS_requested);
    PMNonValHash.insert("RESET_GEN_BUNCH_OFFSET",      &MyDimServer::apply_RESET_GEN_BUNCH_OFFSET_requested);
    PMNonValHash.insert("RESET_GBT_ERRORS",            &MyDimServer::apply_RESET_GBT_ERRORS_requested);
    PMNonValHash.insert("RESET_GBT",                   &MyDimServer::apply_RESET_GBT_requested);
    PMNonValHash.insert("RESET_RX_PHASE_ERROR",        &MyDimServer::apply_RESET_RX_PHASE_ERROR_requested);
//////////////////////////////    PMNonValHash.insert("SEND_COMMAND",                &MyDimServer::apply_SEND_COMMAND_requested);
//////////////////////////////    PMNonValHash.insert("TG_MODE",                     &MyDimServer::apply_TG_MODE_requested);
    PMNonValHash.insert("TG_PATTERN_1",                 &MyDimServer::apply_TG_PATTERN_1_requested);
    PMNonValHash.insert("TG_PATTERN_0",                 &MyDimServer::apply_TG_PATTERN_0_requested);
    PMNonValHash.insert("TG_CONT_VALUE",               &MyDimServer::apply_TG_CONT_VALUE_requested);
//////////////////////////////    PMNonValHash.insert("TG_SEND_SINGLE",              &MyDimServer::apply_TG_SEND_SINGLE_requested);
    PMNonValHash.insert("TG_BUNCH_FREQ",               &MyDimServer::apply_TG_BUNCH_FREQ_requested);
    PMNonValHash.insert("TG_FREQ_OFFSET",              &MyDimServer::apply_TG_FREQ_OFFSET_requested);
//////////////////////////////    PMNonValHash.insert("DG_MODE",                     &MyDimServer::apply_DG_MODE_requested);
    PMNonValHash.insert("DG_TRG_RESPOND_MASK",         &MyDimServer::apply_DG_TRG_RESPOND_MASK_requested);
    PMNonValHash.insert("DG_BUNCH_PATTERN",            &MyDimServer::apply_DG_BUNCH_PATTERN_requested);
    PMNonValHash.insert("DG_BUNCH_FREQ",               &MyDimServer::apply_DG_BUNCH_FREQ_requested);
    PMNonValHash.insert("DG_FREQ_OFFSET",              &MyDimServer::apply_DG_FREQ_OFFSET_requested);
    PMNonValHash.insert("RDH_FEE_ID",                  &MyDimServer::apply_RDH_FEE_ID_requested);
    PMNonValHash.insert("RDH_PAR",                     &MyDimServer::apply_RDH_PAR_requested);
    PMNonValHash.insert("RDH_MAX_PAYLOAD",             &MyDimServer::apply_RDH_MAX_PAYLOAD_requested);
    PMNonValHash.insert("RDH_DET_FIELD",               &MyDimServer::apply_RDH_DET_FIELD_requested);
    PMNonValHash.insert("CRU_TRG_COMPARE_DELAY",       &MyDimServer::apply_CRU_TRG_COMPARE_DELAY_requested);
    PMNonValHash.insert("BCID_DELAY",                  &MyDimServer::apply_BCID_DELAY_requested);
    PMNonValHash.insert("ALLtoPM",                     &MyDimServer::apply_ALLtoPM_requested);

}

void fillPMCHNonValHash()
{
     PMCHNonValHash.insert("ADC_ZERO",    &MyDimServer::apply_ADC_ZERO_requested);
     PMCHNonValHash.insert("ADC_DELAY",   &MyDimServer::apply_ADC_DELAY_requested);
     PMCHNonValHash.insert("ADC0_OFFSET", &MyDimServer::apply_ADC0_OFFSET_requested);
     PMCHNonValHash.insert("ADC1_OFFSET", &MyDimServer::apply_ADC1_OFFSET_requested);
     PMCHNonValHash.insert("ADC0_RANGE",  &MyDimServer::apply_ADC0_RANGE_requested);
     PMCHNonValHash.insert("ADC1_RANGE",  &MyDimServer::apply_ADC1_RANGE_requested);
     PMCHNonValHash.insert("TIME_ALIGN",   &MyDimServer::apply_TIME_ALIGN_requested);
     PMCHNonValHash.insert("CFD_TRHESHOLD",&MyDimServer::apply_CFD_THRESHOLD_requested);
     PMCHNonValHash.insert("CFD_ZERO",    &MyDimServer::apply_CFD_ZERO_requested);
     PMCHNonValHash.insert("THRESHOLD_CALIBR",&MyDimServer::apply_THRESHOLD_CALIBR_requested);
     PMCHNonValHash.insert("ALLtoCh",     &MyDimServer::apply_ALLtoCh_requested);

}

pm_APP::pm_APP(QString t_name) : Base(t_name)
{
//    pAPPSignal = returnPMAppPointerToSignal(name);
}

void pm_APP::publishCommand()
{
//    if(pSet != nullptr)
    appCommand = new DimCommand(qPrintable("APP_FT0/PM"+PM_Names[PMid]
                                        +prefix+"/"+name),"C:1",this);
    outDCs << appCommand->getName() << endl;
    SetSignal();
}

void pm_APP::commandHandler()
{
    DimCommand* currCmnd = getCommand();
    if(currCmnd == appCommand) {
        cout << "@APP@ recieved " << currCmnd->getName() << endl;
        emitSignalRequest();
    }
}

void pm_APP::emitSignalRequest()
{
    pServer->emitSignal(pAPPSignal,PMid);
}

void pm_APP::SetSignal(){ pAPPSignal = getPMNonValPointerToSignal(this->name);}


pmch_APP::pmch_APP(QString t_name) : Base(t_name), pm_APP::pm_APP(t_name)
{
//    this->prefix = "/Ch"+QString("%1").arg(CHid,2,10,QLatin1Char('0')) + this->prefix;
    SetSignal();
}

void pmch_APP::emitSignalRequest()
{
    this->pServer->emitSignal(pAPPSignal,this->PMid,this->CHid);
}

void pmch_APP::SetSignal(){ pAPPSignal = getPMCHNonValPointerToSignal(this->name);}

PMonlyAppPar::PMonlyAppPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control/GBT"), pm_APP(t_name)
{this->SetServer(t_pServer);}

void PMonlyAppPar::publishCommands()
{ pm_APP::publishCommand(); }

PMCHonlyAppPar::PMCHonlyAppPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control"), pmch_APP(t_name)
{this->SetServer(t_pServer);}

void PMCHonlyAppPar::publishCommands()
{ pmch_APP::publishCommand(); }
