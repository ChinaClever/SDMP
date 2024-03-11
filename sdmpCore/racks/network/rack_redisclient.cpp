/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_redisclient.h"

Rack_RedisClient::Rack_RedisClient() {}

void Rack_RedisClient::rack_work()
{
    sCfgRedisUnit *unit = &CfgCom::mCfgRedis.rack;
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
            QString fmd = "%1:%2:%3"; QString key = unit->key;
            QString topic = fmd.arg(room, cab, name);
            hset(key,topic, json); //cout << topic;
        }
    }
}
