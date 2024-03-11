/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_redisclient.h"
#include "rooms/sqls/room_indexsql.h"
Aisle_RedisClient::Aisle_RedisClient() {}

void Aisle_RedisClient::aisle_work()
{
    sCfgRedisUnit *unit = &CfgCom::mCfgRedis.aisle;
    if(compareTime(unit)) {
        Aisle_IndexSql *index = Aisle_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = Room_IndexSql::build()->getNameById(index->roomId(id));
            QString aisle = index->getNameById(id); QJsonObject json;
            json.insert("power", Aisle_HdaSql::build()->aisleHdaJson(id));
            json.insert("ele", Aisle_EleSql::build()->aisleEleJson(id));
            QString fmd = "%1:%2"; QString key = unit->key;
            QString topic = fmd.arg(room, aisle);
            hset(key, topic, json); //cout << topic;
        }
    }
}
