#ifndef ROOM_REDISCLIENT_H
#define ROOM_REDISCLIENT_H
#include "../sqls/room_hdasql.h"
#include "aisles/network/aisle_httpserver.h"

class Room_RedisClient : public Aisle_RedisClient
{
public:
    Room_RedisClient();
    void room_work();
};

#endif // ROOM_REDISCLIENT_H
