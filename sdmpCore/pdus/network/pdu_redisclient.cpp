/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_redisclient.h"

Pdu_RedisClient::Pdu_RedisClient()
{

}


bool Pdu_RedisClient::compareTime(sCfgRedisUnit *unit)
{
    bool ret = false; if(unit->en && unit->interval) {
        QDateTime t = unit->last_time.addSecs(unit->interval);
        QDateTime c = QDateTime::currentDateTime();
        if(c > t) {ret = true; unit->last_time = c;}
    }
    return ret;
}

void Pdu_RedisClient::pdu_work()
{
    sCfgRedisUnit *unit = &CfgCom::mCfgRedis.pdu;
    Pdu_NetJsonPack *obj = Pdu_NetJsonPack::build();
    QStringList lst; QString prefix = unit->key;
    if(compareTime(unit)) {
        lst = obj->online_list();
        pdu_online(lst, prefix);
    } else {
        lst = obj->alarm_list();
        prefix = "pduAlarmKey";
        pdu_alarm(lst, prefix);
    }
}

void Pdu_RedisClient::pdu_online(const QStringList &lst, const QString &key)
{
    foreach (const auto &it, lst) {
        QString fmd = "%1:%2";
        QJsonObject json = Pdu_NetJsonPack::build()->meta(it);
        QString ip = json.value("ip").toString();
        int addr = json.value("addr").toInt();
        QString field = fmd.arg(ip).arg(addr);
        hset(key, field, json); //cout << topic;
    }
}

void Pdu_RedisClient::pdu_alarm(const QStringList &lst, const QString &key)
{
    Pdu_NetJsonPack *obj = Pdu_NetJsonPack::build();
    QString ip; uchar addr; foreach (const auto &it, lst) {
        QString fmd = "%1:/%2";
        QString alarm = Pdu_NetJsonPack::build()->alarm(it);
        obj->getByKey(it, ip, addr); //cout << alarm;
        QString field = fmd.arg(ip).arg(addr);
        hset(key, field, alarm.toUtf8());
    }
}
