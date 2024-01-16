/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "dbcorethread.h"

DbCoreThread::DbCoreThread(QObject *parent)
    : Cab_HttpServer{parent}
{
    this->http_listen(43796);
    mTimer = new QTimer(this); mTimer->start(1000);
    connect(mTimer, &QTimer::timeout, this, &DbCoreThread::onTimeout);

}

void DbCoreThread::initFun()
{
    static bool initialized=false;
    if(initialized) return ; else initialized=true;
    Pdu_LogSql::build(); Pdu_IndexSql::build()->initFun();





}

void DbCoreThread::syncWork()
{
    Pdu_IndexSql::build()->syncNetPack();
    Cab_IndexSql::build()->syncFun();
    Aisle_IndexSql::build()->syncFun();
    Room_IndexSql::build()->syncFun();
    Rack_IndexSql::build()->syncFun();
    Aisle_IndexSql::build()->syncFun();
    Aisle_BarSql::build()->initFun();
    Cab_PduSql::build()->initFun();
}

void DbCoreThread::hdaWork()
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    if(it->hda_en && it->hda_interval) {
        // QDateTime t = it->hda_last_time.addSecs(it->hda_interval *60);
        // if(QDateTime::currentDateTime() > t) {
            it->hda_last_time = QDateTime::currentDateTime();
            Pdu_HdaSql::build()->hdaWork();
            Cab_HdaSql::build()->workDown();
            Aisle_HdaSql::build()->hdaWork();
            Room_HdaSql::build()->hdaWork();
            Rack_HdaSql::build()->hdaWork();

        // }
    }
}

void DbCoreThread::eleWork()
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    if(it->ele_en && it->ele_interval) {
        // QDateTime t = it->ele_last_time.addSecs(it->ele_interval*60*60);
        // if(QDateTime::currentDateTime() > t) {
            it->ele_last_time = QDateTime::currentDateTime();
            Pdu_EleSql::build()->eleWork();
            Cab_EleSql::build()->workDown();
            Aisle_EleSql::build()->eleWork();
            Room_EleSql::build()->eleWork();
            Rack_EleSql::build()->eleWork();


        // }
    }
}

void DbCoreThread::alarmWork()
{
    Pdu_LogSql::build()->workDown();
    Cab_Alarm::build()->alarmWork();
}


void DbCoreThread::workDown()
{
    initFun();
    syncWork();
    alarmWork();
    hdaWork();
    eleWork();

    cout << "AAAAAAAAAA";

}

void DbCoreThread::run()
{
    if(isRun) return; else isRun=true;
    mCnt++; workDown();
    isRun = false;
}
