/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_mqttpublish.h"

Room_MqttPublish::Room_MqttPublish()
{

}


void Room_MqttPublish::room_work()
{
    sCfgMqttUnit *unit = &CfgCom::mCfgPublish.room;
    if(compareTime(unit)) {
        Room_IndexSql *index = Room_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = index->getNameById(id); QJsonObject json;
            json.insert("power", Room_HdaSql::build()->roomHdaJson(id));
            json.insert("ele", Room_EleSql::build()->roomEleJson(id));
            QString fmd = "%1/%2"; if(m_mqtt->isBusy()) cm_mdelay(1);
            QString topic = fmd.arg(unit->topic, room);
            m_mqtt->append(topic, json); //cout << topic;
        }
    }
}
