#ifndef REDISCLIENTCORE_H
#define REDISCLIENTCORE_H
#include "racks/network/rack_httpserver.h"

class RedisClientCore : public QThread, public Rack_RedisClient
{
    explicit RedisClientCore(QObject *parent = nullptr);
public:
    static RedisClientCore *build(QObject *parent = nullptr);
    ~RedisClientCore();
protected:
    void run();
    void workDown();
    void start_work();
    bool openConnected();

private:
    bool isRun=true;
};

#endif // REDISCLIENTCORE_H
