/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_redisclient.h"

Room_RedisClient::Room_RedisClient() {}

void Room_RedisClient::room_work()
{
    sCfgRedisUnit *unit = &CfgCom::mCfgRedis.room;
    if(compareTime(unit)) {
        Room_IndexSql *index = Room_IndexSql::build();
        QList<uint> ids = index->getIds();
        foreach (const auto &id, ids) {
            QString room = index->getNameById(id); QJsonObject json;
            json.insert("power", Room_HdaSql::build()->roomHdaJson(id));
            json.insert("ele", Room_EleSql::build()->roomEleJson(id));
            QString fmd = "%1"; QString key = unit->key;
            QString topic = fmd.arg(room);
            hset(key, topic, json); //cout << topic;
        }
    }
}
