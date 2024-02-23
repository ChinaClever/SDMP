/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_mqttpublish.h"

Rack_MqttPublish::Rack_MqttPublish()
{

}

void Rack_MqttPublish::rack_work()
{
    sCfgMqttUnit *unit = &CfgCom::mCfgPublish.rack;
    if(compareTime(unit)) {
        Rack_IndexSql *index = Rack_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString name = index->getNameById(id);
            uint cab_id = index->cabId(id); QJsonObject json;
            QString cab = Cab_IndexSql::build()->getNameById(cab_id);
            uint room_id = Cab_IndexSql::build()->roomId(cab_id);
            QString room = Room_IndexSql::build()->getNameById(room_id);
            json.insert("power", Rack_HdaSql::build()->rackHdaJson(id));
            json.insert("ele", Rack_EleSql::build()->rackEleJson(id));
            QString fmd = "%1/%2/%3/%4"; if(m_mqtt->isBusy()) cm_mdelay(1);
            QString topic = fmd.arg(unit->topic, room, cab, name);
            m_mqtt->append(topic, json); //cout << topic;
        }
    }
}
