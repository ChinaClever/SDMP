/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_mqttpublish.h"

Pdu_MqttPublish::Pdu_MqttPublish()
{
    m_mqtt = Mqtt_Publish::bulid();
}

bool Pdu_MqttPublish::compareTime(sCfgMqttUnit *unit)
{
    bool ret = false; if(unit->en && unit->interval) {
        QDateTime t = unit->last_time.addSecs(unit->interval);
        QDateTime c = QDateTime::currentDateTime();
        if(c > t) {ret = true; unit->last_time = c;}
    }
    return ret;
}

void Pdu_MqttPublish::pdu_work()
{
    sCfgMqttUnit *unit = &CfgCom::mCfgPublish.pdu;
    Pdu_NetJsonPack *obj = Pdu_NetJsonPack::build();
    QStringList lst; QString prefix = unit->topic;
    if(compareTime(unit)) {
        lst = obj->online_list();        
        pdu_online(lst, prefix);
    } else {
        lst = obj->alarm_list();
        prefix = "pduAlarmTopic";
        pdu_alarm(lst, prefix);
    }
}

void Pdu_MqttPublish::pdu_online(const QStringList &lst, const QString &prefix)
{
    foreach (const auto &it, lst) {
        QString fmd = "%1/%2/%3"; if(m_mqtt->isBusy()) cm_mdelay(1);
        QJsonObject json = Pdu_NetJsonPack::build()->meta(it);
        QString ip = json.value("ip").toString();
        int addr = json.value("addr").toInt();
        QString topic = fmd.arg(prefix, ip).arg(addr);
        m_mqtt->append(topic, json); //cout << topic;
    }
}

void Pdu_MqttPublish::pdu_alarm(const QStringList &lst, const QString &prefix)
{
    Pdu_NetJsonPack *obj = Pdu_NetJsonPack::build();
    QString ip; uchar addr; foreach (const auto &it, lst) {
        QString fmd = "%1/%2/%3"; if(m_mqtt->isBusy()) cm_mdelay(1);
        QString alarm = Pdu_NetJsonPack::build()->alarm(it);
        obj->getByKey(it, ip, addr); //cout << alarm;
        QString topic = fmd.arg(prefix, ip).arg(addr);
        m_mqtt->append(topic, alarm.toUtf8());
    }
}
