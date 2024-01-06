/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "dbcorethread.h"

DbCoreThread::DbCoreThread(QObject *parent)
    : QThread{parent}
{
    mTimer = new QTimer(this); mTimer->start(1000);
    connect(mTimer, &QTimer::timeout, this, &DbCoreThread::onTimeout);

}

void DbCoreThread::initFun()
{
    static bool initialized=false;
    if(initialized) return ; else initialized=true;
    Pdu_LogSql::bulid(); Pdu_IndexSql::bulid()->initFun();





}

void DbCoreThread::syncWork()
{
    Pdu_IndexSql::bulid()->syncNetPack();
    Cab_IndexSql::bulid()->syncFun();


}

void DbCoreThread::hdaWork()
{
    sCfgSqlItem *it = &CfgCom::bulid()->mCfgSql;
    if(it->hda_en && it->hda_interval) {
        // QDateTime t = it->hda_last_time.addSecs(it->hda_interval *60);
        // if(QDateTime::currentDateTime() > t) {
            it->hda_last_time = QDateTime::currentDateTime();
            Pdu_HdaSql::bulid()->hdaWork();
            Cab_HdaSql::bulid()->workDown();


        // }
    }
}

void DbCoreThread::eleWork()
{
    sCfgSqlItem *it = &CfgCom::bulid()->mCfgSql;
    if(it->ele_en && it->ele_interval) {
        // QDateTime t = it->ele_last_time.addSecs(it->ele_interval*60*60);
        // if(QDateTime::currentDateTime() > t) {
            it->ele_last_time = QDateTime::currentDateTime();
            Pdu_EleSql::bulid()->eleWork();
            Cab_EleSql::bulid()->workDown();


        // }
    }
}

void DbCoreThread::alarmWork()
{
    Pdu_LogSql::bulid()->workDown();
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
