/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "dbthreadcore.h"

DbThreadCore::DbThreadCore(QObject *parent)
    : HttpServerCore{parent}
{
    mTimer = new QTimer(this); mTimer->start(2500);
    connect(mTimer, &QTimer::timeout, this, &DbThreadCore::onTimeout);
    QTimer::singleShot(1243,this,SLOT(initFunSlot()));
}

DbThreadCore *DbThreadCore::build(QObject *parent)
{
    static DbThreadCore* sington = nullptr;
    if(!sington) sington = new DbThreadCore(parent);
    return sington;
}

DbThreadCore::~DbThreadCore()
{
    isContinue = false;
    // delete m_mqtt;
    //delete m_redis;
    wait();
}

QStringList DbThreadCore::writeMsg()
{
    QStringList res = mWriteLst;
    mWriteLst.clear();
    return res;
}

void DbThreadCore::initFunSlot()
{
    m_mqtt = new MqttPublishCore(this);
    m_redis = RedisClientCore::build(this);
    m_mqtt->start(); m_redis->start();
}

void DbThreadCore::initFun()
{
    static bool initialized=false;
    if(initialized) return; else initialized=true;
    if(isRun()) Pdu_IndexSql::build()->initFun();
    if(isRun()) Pdu_LogSql::build();

}

bool DbThreadCore::isRun()
{
    bool ret = isContinue;
    if(ret) ret = OrmDb::isOpen();
    return ret;
}

void DbThreadCore::syncWork()
{
    if(isRun()) Pdu_IndexSql::build()->syncNetPack();
    if(isRun()) Cab_IndexSql::build()->syncFun();
    if(isRun()) Aisle_IndexSql::build()->syncFun();
    if(isRun()) Room_IndexSql::build()->syncFun();
    if(isRun()) Rack_IndexSql::build()->syncFun();
    if(isRun()) Aisle_IndexSql::build()->syncFun();
    if(isRun()) Aisle_BarSql::build()->initFun();
    if(isRun()) Cab_PduSql::build()->initFun();
}

void DbThreadCore::computetime(const QTime &start, int cnt, const QString &msg)
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

bool DbThreadCore::compareTime(sCfgSqlUnit &unit, int sec)
{
    bool ret = false; if(unit.en && unit.interval) {
        QDateTime t = unit.last_time.addSecs(unit.interval *sec);
        QDateTime c = QDateTime::currentDateTime();
        if(c > t) ret = true;
    } ret = true; //////=======
    return ret;
}

void DbThreadCore::last_time(sCfgSqlUnit &unit)
{
    QDateTime c = QDateTime::currentDateTime(); unit.last_time = c;
    //CfgCom::build()->writeCfg(unit.prefix+"last_time", c, "sql");
}

void DbThreadCore::hdaObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg)
{
    if(!isRun()) return; QTime start = QTime::currentTime();
    if(compareTime(unit, 60)) isWrite = true; else return;
    computetime(start, db->workDown(), msg+tr("数据"));
    last_time(unit);
}

void DbThreadCore::hdaWork()
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    hdaObj(Pdu_HdaSql::build(), it->pdu_hda, tr("PDU"));
    hdaObj(Cab_HdaSql::build(), it->cab_hda, tr("机柜"));
    hdaObj(Aisle_HdaSql::build(),it->aisle_hda, tr("柜列"));
    hdaObj(Room_HdaSql::build(), it->room_hda, tr("机房"));
    hdaObj(Rack_HdaSql::build(), it->rack_hda, tr("机架"));
}


void DbThreadCore::eleObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg)
{    
    if(!isRun()) return; QTime start = QTime::currentTime();
    if(compareTime(unit, 60*60)) isWrite = true; else return;
    computetime(start, db->workDown(), msg+tr("电能"));
    last_time(unit);
}


void DbThreadCore::eleWork()
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    eleObj(Pdu_EleSql::build(), it->pdu_ele, tr("PDU"));
    eleObj(Cab_EleSql::build(), it->cab_ele, tr("机柜"));
    eleObj(Aisle_EleSql::build(),it->aisle_ele, tr("柜列"));
    eleObj(Room_EleSql::build(), it->room_ele, tr("机房"));
    eleObj(Rack_EleSql::build(), it->rack_ele, tr("机架"));
}

void DbThreadCore::alarmWork()
{
    if(isRun()) Pdu_LogSql::build()->workDown();
    if(isRun()) Cab_Alarm::build()->alarmWork();
}


void DbThreadCore::workDown()
{
    if(isRun()) initFun();
    if(isRun()) syncWork();
    if(isRun()) alarmWork();
    if(isRun()) hdaWork();
    if(isRun()) eleWork();

    // cout << "AAAAAAAAAA";

}

void DbThreadCore::run()
{
    if(isContinue) return; else isContinue=true;
    if(OrmDb::isOpen()) workDown();
    isContinue = false;
    isWrite = false;
}
