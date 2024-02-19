/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "dbcorethread.h"

DbCoreThread::DbCoreThread(QObject *parent)
    : Cab_HttpServer{parent}
{
    mTimer = new QTimer(this); //mTimer->start(1000);
    connect(mTimer, &QTimer::timeout, this, &DbCoreThread::onTimeout);
    QTimer::singleShot(243,this,SLOT(initFunSlot()));
}

DbCoreThread *DbCoreThread::build(QObject *parent)
{
    static DbCoreThread* sington = nullptr;
    if(!sington) sington = new DbCoreThread(parent);
    return sington;
}

DbCoreThread::~DbCoreThread()
{
    isRun = false;
    wait();
}

QStringList DbCoreThread::writeMsg()
{
    QStringList res = mWriteLst;
    mWriteLst.clear();
    return res;
}

void DbCoreThread::initFunSlot()
{
    sCfgRestItem *it = &CfgCom::build(this)->mCfgRest;
    if(it->http.en) {
        QHostAddress address(it->http.url);
        switch(it->http.acl) {
        case 1: address = QHostAddress::Any; break;
        case 0: address = QHostAddress::LocalHost; break;
        } this->http_listen(it->http.port, address);
    }

    if(it->https.en) {
        QHostAddress address(it->https.url);
        switch(it->https.acl) {
        case 1: address = QHostAddress::Any; break;
        case 0: address = QHostAddress::LocalHost; break;
        } this->https_listen(it->https.port, address);
    }

    mTimer->start(1000);
}

void DbCoreThread::initFun()
{
    static bool initialized=false;
    if(initialized) return; else initialized=true;
    Pdu_LogSql::build(); Pdu_IndexSql::build()->initFun();





}

void DbCoreThread::syncWork()
{
    if(!isRun||!CfgCom::mCfgDb.en)return;
    Pdu_IndexSql::build()->syncNetPack();
    Cab_IndexSql::build()->syncFun();
    Aisle_IndexSql::build()->syncFun();
    Room_IndexSql::build()->syncFun();
    Rack_IndexSql::build()->syncFun();
    Aisle_IndexSql::build()->syncFun();
    Aisle_BarSql::build()->initFun();
    Cab_PduSql::build()->initFun();
}

void DbCoreThread::computetime(const QTime &start, int cnt, const QString &msg)
{
    QString time_str;
    QTime end = QTime::currentTime();
    int time_difference = start.msecsTo(end);
    int minutes = time_difference / (1000 * 60);
    int seconds = (time_difference / 1000) % 60;
    int milliseconds = time_difference % 1000;
    if(minutes) time_str += QString::number(minutes) + tr("分");
    if(seconds) time_str += QString::number(seconds) + tr("秒");
    if(milliseconds) time_str += QString::number(milliseconds) + tr("毫秒");

    QString fmd = "%1  写入%2条记录  耗时%3";
    if(cnt) mWriteLst << fmd.arg(msg).arg(cnt).arg(time_str);
}

bool DbCoreThread::compareTime(sCfgSqlUnit &unit, int sec)
{
    bool ret = false; if(unit.en && unit.interval) {
        QDateTime t = unit.last_time.addSecs(unit.interval *sec);
        QDateTime c = QDateTime::currentDateTime();
        if(c > t) ret = true;
    } ret = true; //////=======
    return ret;
}

void DbCoreThread::last_time(sCfgSqlUnit &unit)
{
    QDateTime c = QDateTime::currentDateTime(); unit.last_time = c;
    CfgCom::build()->writeCfg(unit.prefix+"last_time", c, "sql");
}

void DbCoreThread::hdaObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg)
{
    if(!isRun) return; QTime start = QTime::currentTime();
    if(compareTime(unit, 60)) isWrite = true; else return;
    computetime(start, db->workDown(), msg+tr("数据"));
    last_time(unit);
}

void DbCoreThread::hdaWork()
{
    if(!isRun || !CfgCom::mCfgDb.en) return ;
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    hdaObj(Pdu_HdaSql::build(), it->pdu_hda, tr("PDU"));
    hdaObj(Cab_HdaSql::build(), it->cab_hda, tr("机柜"));
    hdaObj(Aisle_HdaSql::build(),it->aisle_hda, tr("柜列"));
    hdaObj(Room_HdaSql::build(), it->room_hda, tr("机房"));
    hdaObj(Rack_HdaSql::build(), it->rack_hda, tr("机架"));
}


void DbCoreThread::eleObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg)
{    
    if(!isRun) return; QTime start = QTime::currentTime();
    if(compareTime(unit, 60*60)) isWrite = true; else return;
    computetime(start, db->workDown(), msg+tr("电能"));
    last_time(unit);
}


void DbCoreThread::eleWork()
{
    if(!isRun || !CfgCom::mCfgDb.en) return ;
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    eleObj(Pdu_EleSql::build(), it->pdu_ele, tr("PDU"));
    eleObj(Cab_EleSql::build(), it->cab_ele, tr("机柜"));
    eleObj(Aisle_EleSql::build(),it->aisle_ele, tr("柜列"));
    eleObj(Room_EleSql::build(), it->room_ele, tr("机房"));
    eleObj(Rack_EleSql::build(), it->rack_ele, tr("机架"));
}

void DbCoreThread::alarmWork()
{
    if(!isRun) return;
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
    isWrite = false;
    isRun = false;
}
