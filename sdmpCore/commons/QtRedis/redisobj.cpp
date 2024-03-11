#include "redisobj.h"
#include <QJsonDocument>

RedisObj::RedisObj()
{

}

RedisObj::~RedisObj()
{
    if(mRedis) {
        delete mRedis;
        mRedis = nullptr;
    }
}

bool RedisObj::isConnected()
{
    bool ret = false;
    if(mRedis) ret = mRedis->isConnected();
    return ret;
}

bool RedisObj::connectHost(const QString &host, const quint16 port, const QString &pwd, int db)
{
    bool ret = false;
    if(mRedis) {
        if(m_host !=host || m_port != port)
            mRedis->connectHost(host, port);
        ret = mRedis->isConnected();
    } else {
        mRedis = new QtRedis(host, port);
        ret = mRedis->openConnection();
    } if(pwd.size() && ret) ret = mRedis->auth(pwd);
    if(db && ret) ret = mRedis->select(db);
    m_host = host; m_port = port;
    return ret;
}

bool RedisObj::hset(const QString &key, const QString &field, const QJsonObject &value)
{
    bool ret = isConnected();
    if(ret && mRedis) {
        QJsonDocument jsonDoc(value);
        QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
        ret = mRedis->hset(key, field, jsonString);
    }

    return ret;
}

bool RedisObj::hset(const QString &key, const QString &field, const QString &value)
{
    bool ret = isConnected();
    if(ret && mRedis) ret = mRedis->hset(key, field, value);
    return ret;
}
