#ifndef AISLE_REDISCLIENT_H
#define AISLE_REDISCLIENT_H
#include "../sqls/aisle_hdasql.h"
#include "cabinets/network/cab_httpserver.h"

class Aisle_RedisClient : public Cab_RedisClient
{
public:
    Aisle_RedisClient();
    void aisle_work();
};

#endif // AISLE_REDISCLIENT_H
