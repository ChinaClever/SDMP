/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "redisclientcore.h"

RedisClientCore::RedisClientCore(QObject *parent)
    : QThread{parent}
{

}

RedisClientCore::~RedisClientCore()
{
    isRun = false;
    wait();
}

RedisClientCore *RedisClientCore::build(QObject *parent)
{
    static RedisClientCore* sington = nullptr;
    if(!sington) sington = new RedisClientCore(parent);
    return sington;
}

void RedisClientCore::workDown()
{
    if(isRun) room_work();
    if(isRun) aisle_work();
    if(isRun) cab_work();
    if(isRun) pdu_work();
    if(isRun) rack_work();
}


void RedisClientCore::start_work()
{
    sCfgRedisItem *unit = &CfgCom::mCfgRedis;
    if(unit->en && isRun && isConnected()) workDown();
}

bool RedisClientCore::openConnected()
{
    sCfgRedisItem *unit = &CfgCom::mCfgRedis;
    if(unit->en && !isConnected()) {
         connectHost(unit->host, unit->port, unit->pwd, unit->db);
    }
    return isConnected();
}

void RedisClientCore::run()
{
    sleep(3); while(isRun) {
        // if(openConnected())
            start_work();
        if(isRun) sleep(1); //cout << isRun;
    }
}


