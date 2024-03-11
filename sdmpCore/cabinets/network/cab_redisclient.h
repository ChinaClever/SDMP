#ifndef CAB_REDISCLIENT_H
#define CAB_REDISCLIENT_H
#include "../sqls/cab_hdasql.h"

class Cab_RedisClient : public Pdu_RedisClient
{
public:
    Cab_RedisClient();
    void cab_work();
};

#endif // CAB_REDISCLIENT_H
