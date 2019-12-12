#include "dimclasses.h"

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//template<class T>
//void pm_ACT<T>::publishService()
//{
//    switch (sizeof(T)) {
//    case 1:
//        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",&actValue,1);
//        break;
//    case 2:
//        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",&actValue,2);
//        break;
//    case 4:
//        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",&actValue,4);
//        break;
//    case 8:
//        actService = new DimService(qPrintable("ACT_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",&actValue,8);
//        break;
//    default:
//        cerr << "\n## Underfined size of T\n";
//        Q_ASSERT(1);
//    }
//};

//template<class T>
//void pm_ACT<T>::updateACT(T val)
//{
//    actValue = val;
//    actService->updateService();
//};

////	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//template<class T>
//void pm_NEW<T>::publishService()
//{
//    switch (sizeof(T)) {
//    case 1:
//        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",&newValue,1);
//        break;
//    case 2:
//        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",&newValue,2);
//        break;
//    case 4:
//        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",&newValue,4);
//        break;
//    case 8:
//        newService = new DimService(qPrintable("NEW_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",&newValue,8);
//        break;
//    default:
//        cerr << "\n## Underfined size of T\n";
//        Q_ASSERT(1);
//    }
//};

//template<class T>
//void pm_NEW<T>::updateNEW(T val)
//{
//    newValue = val;
//    newService->updateService();
//};

//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

pm_APP::pm_APP(QString t_name) : Base(t_name)
{
//    pAPPSignal = returnPMAppPointerToSignal(name);
}

void pm_APP::publishCommand()
{
//    if(pSet != nullptr)
    appCommand = new DimCommand(qPrintable("APP_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))
                                        +prefix+"/"+name),"C:1",this);
}

void pm_APP::commandHandler()
{
    DimCommand* currCmnd = getCommand();
    if(currCmnd == appCommand) {
        cout << "@APP@ recieved " << currCmnd->getName() << endl;
//        pServer->emitSignal(pApp,PM);
    }
}


CHPar::CHPar(QString t_name) : Base(t_name)
{}
void CHPar::SetCHid(quint8 t_CHid){
    CHid = t_CHid; this->prefix = "/Ch"+QString("%1").arg(CHid,2,10,QLatin1Char('0')) + this->prefix;
}
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//template<class T>
//void pm_SET<T>::publishCommand()
//{
////    if(pSet!= nullptr)
//    switch (sizeof(T)) {
//    case 1: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"C:1",this);
//        break;
//    case 2: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"S:1",this);
//        break;
//    case 4: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"I:1",this);
//        break;
//    case 8: setCommand = new DimCommand(qPrintable("SET_FT0/PM"+QString("%1").arg(PMid,2,10,QLatin1Char('0'))+prefix+"/"+name),"X:1",this);
//        break;
//    default:
//        Q_ASSERT(1);
//    }
//}

//template<class T>
//void pm_SET<T>::commandHandler()
//{
//    DimCommand* currCmnd = getCommand();
//    if(currCmnd == setCommand) {
//        cout << "@ recieved " << currCmnd->getName() << endl;
////        pServer->emitSignal(pApp,PM);
//    }
//}


//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

