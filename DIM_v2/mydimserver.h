#ifndef MYDIMSERVER_H
#define MYDIMSERVER_H

#include <QDebug>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QVector>
#include <QObject>

#include "../dim_v20r26/dim/dis.hxx"

//#include "dimclasses.h"
static QTextStream cout(stdout);
static QTextStream cin(stdin);
static QTextStream cerr(stderr);

static QFile DimServicesFile("ServicesList_v1_0.txt");
static QFile DimCommandsFile("CommandsList_v1_0.txt");
static QTextStream outDSs(&DimServicesFile);
static QTextStream outDCs(&DimCommandsFile);

class MyDimServer;

template <class T>
using pm_pValSignal = void(MyDimServer::*)(quint8,T);
using pm_pNonValSignal = void(MyDimServer::*)(quint8);

template <class T>
using pmch_pValSignal = void(MyDimServer::*)(quint8,quint8,T);
using pmch_pNonValSignal = void(MyDimServer::*)(quint8,quint8);

template<class T>
QHash<QString,pm_pValSignal<T>> PMValHash;
void fillPMValHash();
template<class T>
pm_pValSignal<T> getPMValPointerToSignal(QString PARname){ return PMValHash<T>[PARname]; };

template<class T>
QHash<QString,pmch_pValSignal<T>> PMCHValHash;
void fillPMCHValHash();
template<class T>
pmch_pValSignal<T> getPMCHValPointerToSignal(QString PARname){ return PMCHValHash<T>[PARname]; };

static QHash<QString,pm_pNonValSignal> PMNonValHash;
void fillPMNonValHash();
pm_pNonValSignal getPMNonValPointerToSignal(QString PARname);

static QHash<QString,pmch_pNonValSignal> PMCHNonValHash;
void fillPMCHNonValHash();
pmch_pNonValSignal getPMCHNonValPointerToSignal(QString PARname);

static QString PM_Names[21] = {"XX",
                               "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9",
                               "C0","C1","C2","C3","C4","C5","C6","C7","C8","C9"};

class Base
{
protected:
    QString name;
//    QString prefix;
    MyDimServer* pServer;
    quint8 PMid;    //  default is 0
    quint8 CHid;    //  default is 0

public:
    QString prefix;
    void SetServer(MyDimServer* t_pServer){ pServer = t_pServer; }
    void SetPMid(quint8 t_PMid){ PMid = t_PMid; }
    Base(QString t_name, QString t_prefix = "")	:	name (t_name), PMid(0), CHid(0), prefix(t_prefix)
    {/*cout << name << " created" << endl;*/}
    ~Base()	{/*cout << name << " deleted" << endl;*/}
};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@  ACT  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
class pm_ACT : public virtual Base
{
protected:
    T actValue;
    DimService* actService = nullptr;
public:
    void updateAct(T val)
    {
        actValue = val;
        actService->updateService();
        cout << "# " << actService->getName() << " updated to" <<
              hex << " H:" << val << dec << " D:" << val << endl << endl;
    }

    void publishService()
    {
        switch (sizeof(T)) {
        case 1:
            actService = new DimService(qPrintable("ACT_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"C:1",&actValue,1);
            outDSs << actService->getName() << endl;
            break;
        case 2:
            actService = new DimService(qPrintable("ACT_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"S:1",&actValue,2);
            outDSs << actService->getName() << endl;
            break;
        case 4:
            actService = new DimService(qPrintable("ACT_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"I:1",&actValue,4);
            outDSs << actService->getName() << endl;
            break;
        case 8:
            actService = new DimService(qPrintable("ACT_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"X:1",&actValue,8);
            outDSs << actService->getName() << endl;
            break;
        default:
            cerr << "\n## Underfined size of T\n";
            Q_ASSERT(1);
        }
    }


    pm_ACT(QString t_name) : Base(t_name), actValue(0){}
    ~pm_ACT(){ delete actService; }
};


template<class T>
class pmch_ACT : public pm_ACT<T>
{
public:
    pmch_ACT(QString t_name) : Base(t_name), pm_ACT<T>::pm_ACT(t_name)
    {
//        this->prefix = "/Ch"+QString("%1").arg(this->CHid,2,10,QLatin1Char('0')) + this->prefix;
    }
};



//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@  NEW  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
class pm_NEW : public virtual Base
{
protected:
    T newValue;
    DimService* newService = nullptr;
public:
    void updateNew(T val)
    {
        newValue = val;
        newService->updateService();
        cout << "# " << newService->getName() << " updated to" <<
              hex << " H:" << val << dec << " D:" << val << endl << endl;
    }

    void publishService()
    {
        switch (sizeof(T)) {
        case 1:
            newService = new DimService(qPrintable("NEW_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"C:1",&newValue,1);
            outDSs << newService->getName() << endl;
            break;
        case 2:
            newService = new DimService(qPrintable("NEW_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"S:1",&newValue,2);
            outDSs << newService->getName() << endl;
            break;
        case 4:
            newService = new DimService(qPrintable("NEW_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"I:1",&newValue,4);
            outDSs << newService->getName() << endl;
            break;
        case 8:
            newService = new DimService(qPrintable("NEW_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"X:1",&newValue,8);
            outDSs << newService->getName() << endl;
            break;
        default:
            cerr << "\n## Underfined size of T\n";
            Q_ASSERT(1);
        }
    }

    T GetNewValue(){return newValue;}

    pm_NEW(QString t_name) : Base(t_name), newValue(0){}
    ~pm_NEW(){ delete newService; }
};

template<class T>
class pmch_NEW : public pm_NEW<T>
{
public:
    pmch_NEW(QString t_name) : Base(t_name), pm_NEW<T>::pm_NEW(t_name)
    {
//        this->prefix = "/Ch"+QString("%1").arg(this->CHid,2,10,QLatin1Char('0')) + this->prefix;
    }
};



//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@  APP  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class pm_APP : public virtual Base, public DimCommandHandler
{
    DimCommand* appCommand = nullptr;
    pm_pNonValSignal pAPPSignal = nullptr;
    void commandHandler();
public:
    void publishCommand();
    virtual void emitSignalRequest();
    virtual void SetSignal();
    pm_APP(QString t_name);
    virtual ~pm_APP(){ delete appCommand;}
};

class pmch_APP : public pm_APP
{
    pmch_pNonValSignal pAPPSignal = nullptr;
public:
    pmch_APP(QString t_name);
    void emitSignalRequest();
    void SetSignal();
};

template<class T>
class pm_ValAPP : public virtual Base, public DimCommandHandler
{
    DimCommand* appCommand = nullptr;
    pm_pValSignal<T> pAPPSignal = nullptr;
    void commandHandler()
    {
        DimCommand* currCmnd = getCommand();
        if(currCmnd == appCommand) {
            cout << "@ValAPP@ recieved " << currCmnd->getName() <<
                 hex << " H:" << *static_cast<T*>(currCmnd->getData()) <<
                 dec << " D:" << *static_cast<T*>(currCmnd->getData()) << endl;
            emitSignalRequest(currCmnd);
        }
    }
    virtual void emitSignalRequest(DimCommand* currCmnd);


public:
    void publishCommand()
    {
    //    if(pSet!= nullptr)
        switch (sizeof(T)) {
        case 1: appCommand = new DimCommand(qPrintable("APP_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"C:1",this);
            outDCs << appCommand->getName() << endl;
            break;
        case 2: appCommand = new DimCommand(qPrintable("APP_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"S:1",this);
            outDCs << appCommand->getName() << endl;
            break;
        case 4: appCommand = new DimCommand(qPrintable("APP_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"I:1",this);
            outDCs << appCommand->getName() << endl;
            break;
        case 8: appCommand = new DimCommand(qPrintable("APP_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"X:1",this);
            outDCs << appCommand->getName() << endl;
            break;
        default:
            Q_ASSERT(1);
        }
    }

    virtual void SetSignal(){ pAPPSignal = getPMValPointerToSignal<T>(this->name);}
    pm_ValAPP(QString t_name) : Base(t_name){ SetSignal(); }
    virtual ~pm_ValAPP(){ delete appCommand;}
};


//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@  SET  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
class pm_SET : public virtual Base, public DimCommandHandler
{
    DimCommand* setCommand = nullptr;
    pm_pValSignal<T> pSETSignal = nullptr;
    void commandHandler()
    {
        DimCommand* currCmnd = getCommand();
        if(currCmnd == setCommand) {
            cout << "@SET@ recieved " << currCmnd->getName() <<
            hex << " H:" << *static_cast<T*>(currCmnd->getData()) <<
            dec << " D:" << *static_cast<T*>(currCmnd->getData()) << endl;

            emitSignalRequest(currCmnd);
        }
    }
    virtual void emitSignalRequest(DimCommand* currCmnd);
public:
    void publishCommand()
    {
    //    if(pSet!= nullptr)
        switch (sizeof(T)) {
        case 1: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"C:1",this);
            outDCs << setCommand->getName() << endl;
            break;
        case 2: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"S:1",this);
            outDCs << setCommand->getName() << endl;
            break;
        case 4: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"I:1",this);
            outDCs << setCommand->getName() << endl;
            break;
        case 8: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+PM_Names[PMid]+prefix+"/"+name),"X:1",this);
            outDCs << setCommand->getName() << endl;
            break;
        default:
            Q_ASSERT(1);
        }
    }

    virtual void SetSignal(){ pSETSignal = getPMValPointerToSignal<T>(this->name);}
    pm_SET(QString t_name) : Base(t_name){ SetSignal(); }
    virtual ~pm_SET(){ delete setCommand;}
};

template<class T>
class pmch_SET : public pm_SET<T>
{
    pmch_pValSignal<T> pSETSignal = nullptr;
public:
    void emitSignalRequest(DimCommand* currCmnd){
        this->pServer->emitSignal(pSETSignal,this->PMid,this->CHid,*static_cast<T*>(currCmnd->getData()));
    }

    void SetSignal(){ pSETSignal = getPMCHValPointerToSignal<T>(this->name);}

    pmch_SET(QString t_name) : Base(t_name), pm_SET<T>::pm_SET(t_name)
    {
//        this->prefix = "/Ch"+QString("%1").arg(this->CHid,2,10,QLatin1Char('0')) + this->prefix;
        SetSignal();
    }
};


//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


template<class T>
class PMfullPar : public pm_ACT<T>, public pm_NEW<T>, public pm_SET<T>, public pm_APP
{
public:
    PMfullPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control/GBT"), pm_ACT<T>(t_name), pm_NEW<T>(t_name),pm_SET<T>(t_name), pm_APP(t_name)
    {SetServer(t_pServer);}
    void publishServices(){
        pm_ACT<T>::publishService();
        pm_NEW<T>::publishService();
    }
    void publishCommands(){
        pm_SET<T>::publishCommand();
        pm_APP::publishCommand();
    }
};


template<class T>
class PMCHfullPar : public pmch_ACT<T>, public pmch_NEW<T>, public pmch_APP, public pmch_SET<T>
{
public:
    PMCHfullPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control"), pmch_ACT<T>(t_name), pmch_NEW<T>(t_name), pmch_APP(t_name), pmch_SET<T>(t_name)
    {this->SetServer(t_pServer);}
    void SetCHid(quint8 t_CHid){
        CHid = t_CHid; this->prefix = "/Ch"+QString("%1").arg(CHid,2,10,QLatin1Char('0')) + this->prefix;
    }
    void publishServices(){
        pmch_ACT<T>::publishService();
        pmch_NEW<T>::publishService();
    }
    void publishCommands(){
        pmch_SET<T>::publishCommand();
        pmch_APP::publishCommand();
    }
};

template<class T>
class PMonlyActPar : public pm_ACT<T>
{
public:
    PMonlyActPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/status/GBT"), pm_ACT<T>(t_name)
    {this->SetServer(t_pServer);}
    void publishServices(){ pm_ACT<T>::publishService(); }
};

template<class T>
class PMCHonlyActPar : public pmch_ACT<T>
{
public:
    PMCHonlyActPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/status"), pmch_ACT<T>(t_name)
    {this->SetServer(t_pServer);}
    void publishServices(){ pmch_ACT<T>::publishService(); }
    void SetCHid(quint8 t_CHid){
        this->CHid = t_CHid; this->prefix = "/Ch"+QString("%1").arg(this->CHid,2,10,QLatin1Char('0')) + this->prefix;
    }

};

class PMonlyAppPar : public pm_APP
{
public:
    PMonlyAppPar(QString t_name, MyDimServer* t_pServer);
    void publishCommands();
};

class PMCHonlyAppPar : public pmch_APP
{
public:
    PMCHonlyAppPar(QString t_name, MyDimServer* t_pServer);
    void SetCHid(quint8 t_CHid){
        this->CHid = t_CHid; this->prefix = "/Ch"+QString("%1").arg(this->CHid,2,10,QLatin1Char('0')) + this->prefix;
    }
    void publishCommands();
};


template<class T>
class PMonlyValAppPar : public pm_ValAPP<T>
{
public:
    PMonlyValAppPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control/GBT"), pm_ValAPP<T>(t_name)
    {this->SetServer(t_pServer);}
    void publishCommands(){ pm_ValAPP<T>::publishCommand(); }
};

template<class T>
class PMActnValAppPar : public PMonlyActPar<T>, public PMonlyValAppPar<T>
{
public:
    PMActnValAppPar(QString t_name, MyDimServer* t_pServer) : Base(t_name,"/control/GBT"), PMonlyActPar<T>(t_name,t_pServer), PMonlyValAppPar<T>(t_name,t_pServer)
    {this->SetServer(t_pServer);}
};



class PMPars
{
public:
    PMPars(MyDimServer* _server);
    ~PMPars();

    MyDimServer* pServer;
    quint8 Nchannels = 12;
    quint8 PMid;
    void publish();

    QVector<PMCHfullPar<qint16>*> adczero;
    QVector<PMCHfullPar<qint16>*> adcdelay;
    QVector<PMCHfullPar<quint16>*> adc0offset;
    QVector<PMCHfullPar<quint16>*> adc1offset;
    QVector<PMCHfullPar<quint16>*> adc0range;
    QVector<PMCHfullPar<quint16>*> adc1range;
    QVector<PMCHfullPar<quint16>*> timealign;
    QVector<PMCHfullPar<qint16>*> cfdthreshold;
    QVector<PMCHfullPar<qint16>*> cfdzero;
    QVector<PMCHfullPar<qint16>*>  thresholdcalibr;

    QVector<PMCHonlyAppPar*> alltoch;

    QVector<PMCHonlyActPar<quint16>*> adc0meanampl;
    QVector<PMCHonlyActPar<quint16>*> adc1meanampl;
    QVector<PMCHonlyActPar<quint16>*> adc0zerolvl;
    QVector<PMCHonlyActPar<quint16>*> adc1zerolvl;
    QVector<PMCHonlyActPar<quint32>*> cfdcnt;
    QVector<PMCHonlyActPar<quint32>*> trgcnt;
    QVector<PMCHonlyActPar<quint16>*> rawtdcdata;

    PMfullPar<quint16>* chmask;
    PMfullPar<quint16>* cfdsatr;
    PMfullPar<quint8>* orgate;
    PMonlyAppPar* resetcounters;
    PMonlyAppPar* zerolvlcalibration;

    PMonlyAppPar* resetorbitsync;
    PMonlyAppPar* resetdrophitcnts;
    PMonlyAppPar* resetgenbunchoffset;
    PMonlyAppPar* resetgbterrors;
    PMonlyAppPar* resetgbt;
    PMonlyAppPar* resetrxphaseerror;
    PMonlyValAppPar<quint8>* sendreadoutcommand;
    PMActnValAppPar<quint8>*  tgmode;
    PMfullPar<quint32>* tgpattern1;
    PMfullPar<quint32>* tgpattern0;
    PMfullPar<quint8>*  tgcontvalue;
    PMonlyValAppPar<quint32>* tgsendsingle;
    PMfullPar<quint16>* tgbunchfreq;
    PMfullPar<quint16>* tgfreqoffset;
    PMActnValAppPar<quint8>* dgmode;
    PMfullPar<quint32>* dgtrgrespondmask;
    PMfullPar<quint32>* dgbunchpattern;
    PMfullPar<quint16>* dgbunchfreq;
    PMfullPar<quint16>* dgfreqoffset;
    PMfullPar<quint16>* rdhfeeid;
    PMfullPar<quint16>* rdhpar;
    PMfullPar<quint16>* rdhmaxpayload;
    PMfullPar<quint16>* rdhdetfield;
    PMfullPar<quint16>* crutrgcomparedelay;
    PMfullPar<quint16>* bciddelay;
    PMonlyAppPar* alltopm;

    PMonlyActPar<quint16>* boardstatus;
    PMonlyActPar<quint16>* temperature;
    PMonlyActPar<quint32>* hdmilink;
    PMonlyActPar<quint16>* bits;
    PMonlyActPar<quint8>* readoutmode;
    PMonlyActPar<quint8>* bcidsyncmode;
    PMonlyActPar<quint8>* rxphase;
    PMonlyActPar<quint32>* cruorbit;
    PMonlyActPar<quint16>* crubc;
    PMonlyActPar<quint16>* rawfifo;
    PMonlyActPar<quint16>* selfifo;
    PMonlyActPar<quint32>* selfirsthit;
    PMonlyActPar<quint16>* sellasthit;
    PMonlyActPar<quint16>* selhitsdropped;
    PMonlyActPar<quint16>* readoutrate;

};

//  #####################################################################################

class MyDimServer   :  public  QObject, public DimServer
{
    Q_OBJECT
public:
    MyDimServer(QString dns_node, QString server_name="FIT DIM SERVER");
    ~MyDimServer();

//    QFile* DimServicesFile;
//    QFile* DimCommandsFile;


    QString serverName;
    QString dnsNode;
    quint8 Npms = 1;
    PMPars* pm[20];

    void startServer();
    void stopServer();

    void OpenOutFile();
    void CloseOutFile();

    void setNChannels(quint8 nch);

    template<class Y>
    void emitSignal(pmch_pValSignal<Y> pSignal,quint8 PMid,quint8 Chid, Y val);
    void emitSignal(pmch_pNonValSignal pSignal,quint8 PMid,quint8 Chid);

    template<class Y>
    void emitSignal(pm_pValSignal<Y> pSignal,quint8 PMid, Y val);
    void emitSignal(pm_pNonValSignal pSignal,quint8 PMid);

signals:
    void set_ADC_ZERO_requested     (quint8 PMid, quint8 CHid, qint16 val);
    void set_ADC_DELAY_requested    (quint8 PMid, quint8 CHid, qint16 val);
    void set_ADC0_OFFSET_requested  (quint8 PMid, quint8 CHid, quint16 val);
    void set_ADC1_OFFSET_requested  (quint8 PMid, quint8 CHid, quint16 val);
    void set_ADC0_RANGE_requested   (quint8 PMid, quint8 CHid, quint16 val);
    void set_ADC1_RANGE_requested   (quint8 PMid, quint8 CHid, quint16 val);
    void set_TIME_ALIGN_requested    (quint8 PMid, quint8 CHid, quint16 val);
    void set_CFD_THRESHOLD_requested (quint8 PMid, quint8 CHid, qint16 val);
    void set_CFD_ZERO_requested     (quint8 PMid, quint8 CHid, qint16 val);
    void set_THRESHOLD_CALIBR_requested(quint8 PMid, quint8 CHid, qint16 val);

    void apply_ADC_ZERO_requested       (quint8 PMid,quint8 CHid);
    void apply_ADC_DELAY_requested      (quint8 PMid,quint8 CHid);
    void apply_ADC0_OFFSET_requested    (quint8 PMid,quint8 CHid);
    void apply_ADC1_OFFSET_requested    (quint8 PMid,quint8 CHid);
    void apply_ADC0_RANGE_requested     (quint8 PMid,quint8 CHid);
    void apply_ADC1_RANGE_requested     (quint8 PMid,quint8 CHid);
    void apply_TIME_ALIGN_requested      (quint8 PMid,quint8 CHid);
    void apply_CFD_THRESHOLD_requested   (quint8 PMid,quint8 CHid);
    void apply_CFD_ZERO_requested       (quint8 PMid,quint8 CHid);
    void apply_THRESHOLD_CALIBR_requested(quint8 PMid,quint8 CHid);
    void apply_ALLtoCh_requested        (quint8 PMid,quint8 CHid);

    void set_CH_MASK_requested  (quint8 PMid, quint16 val);
    void set_CFD_SATR_requested (quint8 PMid, quint16 val);
    void set_OR_GATE_requested  (quint8 PMid, quint8 val);

    void apply_CH_MASK_requested        (quint8 PMid);
    void apply_CFD_SATR_requested       (quint8 PMid);
    void apply_OR_GATE_requested        (quint8 PMid);
    void apply_RESET_COUNTERS_requested (quint8 PMid);
    void apply_ZERO_LVL_CALIBR_requested(quint8 PMid);

//    /////////////////////////////////////////////////////////////

    void apply_RESET_ORBIT_SYNC_requested           (quint8 PMid);
    void apply_RESET_DROPPING_HIT_COUNTERS_requested(quint8 PMid);
    void apply_RESET_GEN_BUNCH_OFFSET_requested     (quint8 PMid);
    void apply_RESET_GBT_ERRORS_requested           (quint8 PMid);
    void apply_RESET_GBT_requested                  (quint8 PMid);
    void apply_RESET_RX_PHASE_ERROR_requested       (quint8 PMid);
    void apply_SEND_READOUT_COMMAND_requested               (quint8 PMid, quint8 cmd);
    void apply_TG_MODE_requested            (quint8 PMid, quint8 val);
    void apply_TG_PATTERN_1_requested       (quint8 PMid);
    void apply_TG_PATTERN_0_requested       (quint8 PMid);
    void apply_TG_CONT_VALUE_requested      (quint8 PMid);
    void apply_TG_SEND_SINGLE_requested     (quint8 PMid, quint32 val);
    void apply_TG_BUNCH_FREQ_requested      (quint8 PMid);
    void apply_TG_FREQ_OFFSET_requested     (quint8 PMid);
    void apply_DG_MODE_requested            (quint8 PMid, quint8 val);
    void apply_DG_TRG_RESPOND_MASK_requested(quint8 PMid);
    void apply_DG_BUNCH_PATTERN_requested   (quint8 PMid);
    void apply_DG_BUNCH_FREQ_requested      (quint8 PMid);
    void apply_DG_FREQ_OFFSET_requested     (quint8 PMid);
    void apply_RDH_FEE_ID_requested         (quint8 PMid);
    void apply_RDH_PAR_requested            (quint8 PMid);
    void apply_RDH_MAX_PAYLOAD_requested    (quint8 PMid);
    void apply_RDH_DET_FIELD_requested      (quint8 PMid);
    void apply_CRU_TRG_COMPARE_DELAY_requested  (quint8 PMid);
    void apply_BCID_DELAY_requested             (quint8 PMid);

    void set_TG_PATTERN_1_requested      (quint8 PMid, quint32 val);
    void set_TG_PATTERN_0_requested      (quint8 PMid, quint32 val);
    void set_TG_CONT_VALUE_requested    (quint8 PMid, quint8 val);
    void set_TG_BUNCH_FREQ_requested    (quint8 PMid, quint16 val);
    void set_TG_FREQ_OFFSET_requested   (quint8 PMid, quint16 val);

    void set_DG_TRG_RESPOND_MASK_requested  (quint8 PMid, quint32 val);
    void set_DG_BUNCH_PATTERN_requested     (quint8 PMid, quint32 val);
    void set_DG_BUNCH_FREQ_requested        (quint8 PMid, quint16 val);
    void set_DG_FREQ_OFFSET_requested       (quint8 PMid, quint16 val);
    void set_RDH_FEE_ID_requested           (quint8 PMid, quint16 val);
    void set_RDH_PAR_requested              (quint8 PMid, quint16 val);
    void set_RDH_MAX_PAYLOAD_requested      (quint8 PMid, quint16 val);
    void set_RDH_DET_FIELD_requested        (quint8 PMid, quint16 val);
    void set_CRU_TRG_COMPARE_DELAY_requested(quint8 PMid, quint16 val);
    void set_BCID_DELAY_requested           (quint8 PMid, quint16 val);

    void apply_ALLtoPM_requested    (quint8 PMid);

public slots:
    void test_slot0(quint8 PMid){ cout << "Slot0 is reached " << PMid << endl; }
    void test_slot1(quint8 PMid, quint16 val){ cout << "Slot1 is reached " << PMid << " " << val << endl; }
    void test_slot2(quint8 PMid, quint8 CHid, quint16 val){ cout << "Slot2 is reached " << PMid << " " << CHid << " " << val << endl; }
    void test_slot3(quint8 PMid, quint8 CHid, qint16 val){ cout << "Slot2 is reached " << PMid << " " << CHid << " " << val << endl; }
    void update_act_ADC_ZERO    (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->adczero[CHid-1]->updateAct(val);}
    void update_act_ADC_DELAY   (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->adcdelay[CHid-1]->updateAct(val);}
    void update_act_ADC0_OFFSET (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0offset[CHid-1]->updateAct(val);}
    void update_act_ADC1_OFFSET (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1offset[CHid-1]->updateAct(val);}
    void update_act_ADC0_RANGE  (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0range[CHid-1]->updateAct(val);}
    void update_act_ADC1_RANGE  (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1range[CHid-1]->updateAct(val);}
    void update_act_TIME_ALIGN   (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->timealign[CHid-1]->updateAct(val);}
    void update_act_CFD_THRESHOLD(quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->cfdthreshold[CHid-1]->updateAct(val);}
    void update_act_CFD_ZERO    (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->cfdzero[CHid-1]->updateAct(val);}
    void update_act_THRESHOLD_CALIBR(quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->thresholdcalibr[CHid-1]->updateAct(val);}

    void update_new_ADC_ZERO    (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->adczero[CHid-1]->updateNew(val);}
    void update_new_ADC_DELAY   (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->adcdelay[CHid-1]->updateNew(val);}
    void update_new_ADC0_OFFSET (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0offset[CHid-1]->updateNew(val);}
    void update_new_ADC1_OFFSET (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1offset[CHid-1]->updateNew(val);}
    void update_new_ADC0_RANGE  (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0range[CHid-1]->updateNew(val);}
    void update_new_ADC1_RANGE  (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1range[CHid-1]->updateNew(val);}
    void update_new_TIME_ALIGN   (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->timealign[CHid-1]->updateNew(val);}
    void update_new_CFD_THRESHOLD(quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->cfdthreshold[CHid-1]->updateNew(val);}
    void update_new_CFD_ZERO    (quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->cfdzero[CHid-1]->updateNew(val);}
    void update_new_THRESHOLD_CALIBR(quint8 PMid, quint8 CHid, qint16 val){pm[PMid-1]->thresholdcalibr[CHid-1]->updateNew(val);}

    void update_act_ADC0_MEANAMPL   (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0meanampl[CHid-1]->updateAct(val);}
    void update_act_ADC1_MEANAMPL   (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1meanampl[CHid-1]->updateAct(val);}
    void update_act_ADC0_ZEROLVL    (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc0zerolvl[CHid-1]->updateAct(val);}
    void update_act_ADC1_ZEROLVL    (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->adc1zerolvl[CHid-1]->updateAct(val);}
    void update_act_CFD_CNT         (quint8 PMid, quint8 CHid, quint32 val){pm[PMid-1]->cfdcnt[CHid-1]->updateAct(val);}
    void update_act_TRG_CNT         (quint8 PMid, quint8 CHid, quint32 val){pm[PMid-1]->trgcnt[CHid-1]->updateAct(val);}
    void update_act_RAW_TDC_DATA    (quint8 PMid, quint8 CHid, quint16 val){pm[PMid-1]->rawtdcdata[CHid-1]->updateAct(val);}

    void update_act_CH_MASK (quint8 PMid, quint16 val){pm[PMid-1]->chmask->updateAct(val);}
    void update_act_CFD_SATR(quint8 PMid, quint16 val){pm[PMid-1]->cfdsatr->updateAct(val);}
    void update_act_OR_GATE (quint8 PMid, quint8 val){pm[PMid-1]->orgate->updateAct(val);}

    void update_new_CH_MASK (quint8 PMid, quint16 val){pm[PMid-1]->chmask->updateNew(val);}
    void update_new_CFD_SATR(quint8 PMid, quint16 val){pm[PMid-1]->cfdsatr->updateNew(val);}
    void update_new_OR_GATE (quint8 PMid, quint8 val){pm[PMid-1]->orgate->updateNew(val);}

    void update_act_TG_MODE                 (quint8 PMid, quint8 val){pm[PMid-1]->tgmode->updateAct(val);}
    void update_act_TG_PATTERN_1             (quint8 PMid, quint32 val){pm[PMid-1]->tgpattern1->updateAct(val);}
    void update_act_TG_PATTERN_0             (quint8 PMid, quint32 val){pm[PMid-1]->tgpattern0->updateAct(val);}
    void update_act_TG_CONT_VALUE           (quint8 PMid, quint8 val){pm[PMid-1]->tgcontvalue->updateAct(val);}
    void update_act_TG_BUNCH_FREQ           (quint8 PMid, quint16 val){pm[PMid-1]->tgbunchfreq->updateAct(val);}
    void update_act_TG_FREQ_OFFSET          (quint8 PMid, quint16 val){pm[PMid-1]->tgfreqoffset->updateAct(val);}
    void update_act_DG_MODE                 (quint8 PMid, quint8 val){pm[PMid-1]->dgmode->updateAct(val);}
    void update_act_DG_TRG_RESPOND_MASK     (quint8 PMid, quint32 val){pm[PMid-1]->dgtrgrespondmask->updateAct(val);}
    void update_act_DG_BUNCH_PATTERN        (quint8 PMid, quint32 val){pm[PMid-1]->dgbunchpattern->updateAct(val);}
    void update_act_DG_BUNCH_FREQ           (quint8 PMid, quint16 val){pm[PMid-1]->dgbunchfreq->updateAct(val);}
    void update_act_DG_FREQ_OFFSET          (quint8 PMid, quint16 val){pm[PMid-1]->dgfreqoffset->updateAct(val);}
    void update_act_RDH_FEE_ID              (quint8 PMid, quint16 val){pm[PMid-1]->rdhfeeid->updateAct(val);}
    void update_act_RDH_PAR                 (quint8 PMid, quint16 val){pm[PMid-1]->rdhpar->updateAct(val);}
    void update_act_RDH_MAX_PAYLOAD         (quint8 PMid, quint16 val){pm[PMid-1]->rdhmaxpayload->updateAct(val);}
    void update_act_RDH_DET_FIELD           (quint8 PMid, quint16 val){pm[PMid-1]->rdhdetfield->updateAct(val);}
    void update_act_CRU_TRG_COMPARE_DELAY   (quint8 PMid, quint16 val){pm[PMid-1]->crutrgcomparedelay->updateAct(val);}
    void update_act_BCID_DELAY              (quint8 PMid, quint16 val){pm[PMid-1]->bciddelay->updateAct(val);}


    void update_new_TG_PATTERN_1             (quint8 PMid, quint32 val){pm[PMid-1]->tgpattern1->updateNew(val);}
    void update_new_TG_PATTERN_0             (quint8 PMid, quint32 val){pm[PMid-1]->tgpattern0->updateNew(val);}
    void update_new_TG_CONT_VALUE           (quint8 PMid, quint8 val){pm[PMid-1]->tgcontvalue->updateNew(val);}
    void update_new_TG_BUNCH_FREQ           (quint8 PMid, quint16 val){pm[PMid-1]->tgbunchfreq->updateNew(val);}
    void update_new_TG_FREQ_OFFSET          (quint8 PMid, quint16 val){pm[PMid-1]->tgfreqoffset->updateNew(val);}

    void update_new_DG_TRG_RESPOND_MASK     (quint8 PMid, quint32 val){pm[PMid-1]->dgtrgrespondmask->updateNew(val);}
    void update_new_DG_BUNCH_PATTERN        (quint8 PMid, quint32 val){pm[PMid-1]->dgbunchpattern->updateNew(val);}
    void update_new_DG_BUNCH_FREQ           (quint8 PMid, quint16 val){pm[PMid-1]->dgbunchfreq->updateNew(val);}
    void update_new_DG_FREQ_OFFSET          (quint8 PMid, quint16 val){pm[PMid-1]->dgfreqoffset->updateNew(val);}
    void update_new_RDH_FEE_ID              (quint8 PMid, quint16 val){pm[PMid-1]->rdhfeeid->updateNew(val);}
    void update_new_RDH_PAR                 (quint8 PMid, quint16 val){pm[PMid-1]->rdhpar->updateNew(val);}
    void update_new_RDH_MAX_PAYLOAD         (quint8 PMid, quint16 val){pm[PMid-1]->rdhmaxpayload->updateNew(val);}
    void update_new_RDH_DET_FIELD           (quint8 PMid, quint16 val){pm[PMid-1]->rdhdetfield->updateNew(val);}
    void update_new_CRU_TRG_COMPARE_DELAY   (quint8 PMid, quint16 val){pm[PMid-1]->crutrgcomparedelay->updateNew(val);}
    void update_new_BCID_DELAY              (quint8 PMid, quint16 val){pm[PMid-1]->bciddelay->updateNew(val);}

    void update_act_BOARD_STATUS                (quint8 PMid, quint16 val){pm[PMid-1]->boardstatus->updateAct(val);}
    void update_act_TEMPERATURE                 (quint8 PMid, quint16 val){pm[PMid-1]->temperature->updateAct(val);}
    void update_act_HDMI_LINK                   (quint8 PMid, quint32 val){pm[PMid-1]->hdmilink->updateAct(val);}
    void update_act_BITS                        (quint8 PMid, quint16 val){pm[PMid-1]->bits->updateAct(val);}
    void update_act_READOUT_MODE                (quint8 PMid, quint8 val){pm[PMid-1]->readoutmode->updateAct(val);}
    void update_act_BCID_SYNC_MODE              (quint8 PMid, quint8 val){pm[PMid-1]->bcidsyncmode->updateAct(val);}
    void update_act_RX_PHASE                    (quint8 PMid, quint8 val){pm[PMid-1]->rxphase->updateAct(val);}
    void update_act_CRU_ORBIT                   (quint8 PMid, quint32 val){pm[PMid-1]->cruorbit->updateAct(val);}
    void update_act_CRU_BC                      (quint8 PMid, quint16 val){pm[PMid-1]->crubc->updateAct(val);}
    void update_act_RAW_FIFO                    (quint8 PMid, quint16 val){pm[PMid-1]->rawfifo->updateAct(val);}
    void update_act_SEL_FIFO                    (quint8 PMid, quint16 val){pm[PMid-1]->selfifo->updateAct(val);}
    void update_act_SEL_FIRST_HIT_DROPPED_ORBIT (quint8 PMid, quint32 val){pm[PMid-1]->selfirsthit->updateAct(val);}
    void update_act_SEL_LAST_HIT_DROPPED_ORBIT  (quint8 PMid, quint16 val){pm[PMid-1]->sellasthit->updateAct(val);}
    void update_act_SEL_HITS_DROPPED            (quint8 PMid, quint16 val){pm[PMid-1]->selhitsdropped->updateAct(val);}
    void update_act_READOUT_RATE                (quint8 PMid, quint16 val){pm[PMid-1]->readoutrate->updateAct(val);}
};


//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
void pm_SET<T>::emitSignalRequest(DimCommand* currCmnd){
    pServer->emitSignal(pSETSignal,PMid,*static_cast<T*>(currCmnd->getData()));
}

template<class T>
void pm_ValAPP<T>::emitSignalRequest(DimCommand* currCmnd){
    pServer->emitSignal(pAPPSignal,PMid,*static_cast<T*>(currCmnd->getData()));
}


#endif // MYDIMSERVER_H
