/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_redisclient.h"
#include "rooms/sqls/room_indexsql.h"
Cab_RedisClient::Cab_RedisClient() {}


void Cab_RedisClient::cab_work()
{
    sCfgRedisUnit *unit = &CfgCom::mCfgRedis.cab;
    if(compareTime(unit)) {
        Cab_IndexSql *index = Cab_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = Room_IndexSql::build()->getNameById(index->roomId(id));
            QString cab = index->getNameById(id); QJsonObject json;
            json.insert("power", Cab_HdaSql::build()->cabHdaJson(id));
            json.insert("ele", Cab_EleSql::build()->cabEleJson(id));
            QString fmd = "%1:%2"; QString key = unit->key;
            QString topic = fmd.arg(room, cab);
            hset(key, topic, json); //cout << topic;
        }
    }
}
