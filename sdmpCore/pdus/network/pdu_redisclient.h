#ifndef PDU_REDISCLIENT_H
#define PDU_REDISCLIENT_H
#include "httpserverobj.h"
#include "pdu_netjsonpack.h"
#include "commons/mqtt/mqtt_publish.h"
#include "commons/QtRedis/redisobj.h"
#include "commons/print.h"

class Pdu_RedisClient : public RedisObj
{
public:
    Pdu_RedisClient();
    bool compareTime(sCfgRedisUnit *unit);
    void pdu_work();

private:
    void pdu_online(const QStringList &lst, const QString &key);
    void pdu_alarm(const QStringList &lst, const QString &key);
};

#endif // PDU_REDISCLIENT_H
