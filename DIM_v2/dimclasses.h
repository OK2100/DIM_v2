#ifndef DIMCLASSES_H
#define DIMCLASSES_H

#include <QString>
#include <QTextStream>

#include "../dim_v20r26/dim/dis.hxx"

static QTextStream cout(stdout);
static QTextStream cin(stdin);
static QTextStream cerr(stderr);

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
pm_pValSignal<T> getPMValPointerToSignal(QString PARname);




class Base
{
protected:
    QString name;
    QString prefix;
    MyDimServer* pServer;
    quint8 PMid;    //  default is 0

public:
    void SetServer(MyDimServer* t_pServer){ pServer = t_pServer; }
    void SetPMid(quint8 t_PMid){ PMid = t_PMid; }
    Base(QString t_name, QString t_prefix = "")	:	name (t_name), prefix(t_prefix), PMid(0)
    {/*cout << name << " created" << endl;*/}
    ~Base()	{/*cout << name << " deleted" << endl;*/}
};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
class pm_ACT : public virtual Base
{
protected:
    T actValue;
    DimService* actService = nullptr;
//    void publishService();
    void updateACT(T val);
public:
    void publishService();
    pm_ACT(QString t_name) : Base(t_name), actValue(0){}
    ~pm_ACT(){ delete actService; }
};


template<class T>
void pm_ACT<T>::publishService()
{
    switch (sizeof(T)) {
    case 1:
        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",&actValue,1);
        break;
    case 2:
        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",&actValue,2);
        break;
    case 4:
        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",&actValue,4);
        break;
    case 8:
        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",&actValue,8);
        break;
    default:
        cerr << "\n## Underfined size of T\n";
        Q_ASSERT(1);
    }
};


template<class T>
void pm_ACT<T>::updateACT(T val)
{
    actValue = val;
    actService->updateService();
};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

template<class T>
class pm_NEW : public virtual Base
{
protected:
    T newValue;
    DimService* newService = nullptr;
//    void publishService();
    void updateNEW(T val);
public:
    void publishService();
    pm_NEW(QString t_name) : Base(t_name), newValue(0){}
    ~pm_NEW(){ /*delete newService;*/ }
};

template<class T>
void pm_NEW<T>::publishService()
{
    switch (sizeof(T)) {
    case 1:
        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",&newValue,1);
        break;
    case 2:
        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",&newValue,2);
        break;
    case 4:
        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",&newValue,4);
        break;
    case 8:
        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",&newValue,8);
        break;
    default:
        cerr << "\n## Underfined size of T\n";
        Q_ASSERT(1);
    }
};

template<class T>
void pm_NEW<T>::updateNEW(T val)
{
    newValue = val;
    newService->updateService();
};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class pm_APP : public virtual Base, public DimCommandHandler
{
    DimCommand* appCommand = nullptr;
    pm_pNonValSignal pAPPSignal = nullptr;
    void commandHandler();
public:
    void publishCommand();
    pm_APP(QString t_name);
    ~pm_APP(){ /*delete appCommand;*/}
};


class CHPar : public virtual Base
{
    quint8 CHid;
public:
    CHPar(QString t_name);
    void SetCHid(quint8 t_CHid);
};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


template<class T>
class pm_SET : public virtual Base, public DimCommandHandler
{
    DimCommand* setCommand = nullptr;
    pm_pValSignal<T> pSETSignal = nullptr;
    void commandHandler();
public:
    void publishCommand();
    void SetSignal(){ pSETSignal = getPMValPointerToSignal(name); cout << pSETSignal << endl;}
    pm_SET(QString t_name) : Base(t_name){}
    ~pm_SET(){ delete setCommand;}
};


template<class T>
void pm_SET<T>::publishCommand()
{
//    if(pSet!= nullptr)
    switch (sizeof(T)) {
    case 1: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",this);
        break;
    case 2: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",this);
        break;
    case 4: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",this);
        break;
    case 8: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",this);
        break;
    default:
        Q_ASSERT(1);
    }
}

template<class T>
void pm_SET<T>::commandHandler()
{
    DimCommand* currCmnd = getCommand();
    if(currCmnd == setCommand) {
        cout << "@SET@ recieved " << currCmnd->getName() << endl;
//        pServer->emitSignal(pApp,PM);
    }
}



//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


template<class T>
class pm_FULL : public pm_ACT<T>, public pm_NEW<T>, public pm_APP, public pm_SET<T>
{
public:
    pm_FULL(QString t_name) : Base(t_name,"/control"), pm_ACT<T>(t_name), pm_NEW<T>(t_name), pm_APP(t_name),pm_SET<T>(t_name)
    {}
    void publishServices(){
        pm_ACT<T>::publishService();
        pm_NEW<T>::publishService();
    }
    void publishCommands(){
        pm_APP::publishCommand();
        pm_SET<T>::publishCommand();
    }
};



template<class T>
class pmch_ACT : public pm_ACT<T>
{
protected:
    quint8 CHid;
public:
    pmch_ACT(QString t_name);
};

template<class T>
pmch_ACT<T>::pmch_ACT(QString t_name) : Base(t_name), pm_ACT<T>::pm_ACT(t_name), CHid(0)
{
    this->prefix = "/Ch"+QString("%1").arg(CHid,2,10,QLatin1Char('0')) + this->prefix;
};



#endif // DIMCLASSES_H
