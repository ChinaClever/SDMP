#ifndef REDISOBJ_H
#define REDISOBJ_H
#include "qtredis.h"

class RedisObj
{
public:
    RedisObj();
    ~RedisObj();

    bool connectHost(const QString &host, const quint16 port = 6379, const QString &pwd="", int db=0);
    bool hset(const QString &key, const QString &field, const QJsonObject &value);
    bool hset(const QString &key, const QString &field, const QString &value);
    bool isConnected();

protected:
    QtRedis *mRedis=nullptr;
    QString m_host;
    quint16 m_port;
};

#endif // REDISOBJ_H
