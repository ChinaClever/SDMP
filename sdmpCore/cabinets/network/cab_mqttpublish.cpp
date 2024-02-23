/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_mqttpublish.h"
#include "rooms/sqls/room_indexsql.h"

Cab_MqttPublish::Cab_MqttPublish()
{

}

void Cab_MqttPublish::cab_work()
{
    sCfgMqttUnit *unit = &CfgCom::mCfgPublish.cab;
    if(compareTime(unit)) {
        Cab_IndexSql *index = Cab_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = Room_IndexSql::build()->getNameById(index->roomId(id));
            QString cab = index->getNameById(id); QJsonObject json;
            json.insert("power", Cab_HdaSql::build()->cabHdaJson(id));
            json.insert("ele", Cab_EleSql::build()->cabEleJson(id));
            QString fmd = "%1/%2/%3"; if(m_mqtt->isBusy()) cm_mdelay(1);
            QString topic = fmd.arg(unit->topic, room, cab);
            m_mqtt->append(topic, json); //cout << topic;
        }
    }
}
