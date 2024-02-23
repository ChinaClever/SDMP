/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_mqttpublish.h"
#include "rooms/sqls/room_indexsql.h"

Aisle_MqttPublish::Aisle_MqttPublish()
{

}

void Aisle_MqttPublish::aisle_work()
{
    sCfgMqttUnit *unit = &CfgCom::mCfgPublish.aisle;
    if(compareTime(unit)) {
        Aisle_IndexSql *index = Aisle_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = Room_IndexSql::build()->getNameById(index->roomId(id));
            QString aisle = index->getNameById(id); QJsonObject json;
            json.insert("power", Aisle_HdaSql::build()->aisleHdaJson(id));
            json.insert("ele", Aisle_EleSql::build()->aisleEleJson(id));
            QString fmd = "%1/%2/%3"; if(m_mqtt->isBusy()) cm_mdelay(1);
            QString topic = fmd.arg(unit->topic, room, aisle);
            m_mqtt->append(topic, json); //cout << topic;
        }
    }
}
