#ifndef RACK_REDISCLIENT_H
#define RACK_REDISCLIENT_H
#include "rooms/network/room_httpserver.h"
#include "../sqls/rack_hdasql.h"

class Rack_RedisClient : public Room_RedisClient
{
public:
    Rack_RedisClient();
    void rack_work();
};

#endif // RACK_REDISCLIENT_H
