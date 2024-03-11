#ifndef DBTHREADCORE_H
#define DBTHREADCORE_H
#include "httpservercore.h"

class DbThreadCore : public HttpServerCore
{
    Q_OBJECT
    explicit DbThreadCore(QObject *parent = nullptr);
public:
    static DbThreadCore *build(QObject *parent = nullptr);
    bool writing(){return isWrite;}
    QStringList writeMsg();
    ~DbThreadCore();
    void initFun();

protected:
    void run();
    bool isRun();
    void syncWork();
    void hdaWork();
    void eleWork();
    void alarmWork();
    void workDown();
    void eleObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg);
    void hdaObj(OrmDb *db, sCfgSqlUnit &unit, const QString &msg);
    void computetime(const QTime &start, int cnt, const QString &msg);
    bool compareTime(sCfgSqlUnit &unit, int sec);
    void last_time(sCfgSqlUnit &unit);


private slots:
    void onTimeout() {start();}
    void initFunSlot();

private:
    bool isContinue = false;
    bool isWrite = false;
    QStringList mWriteLst;
    QTimer *mTimer = nullptr;
    MqttPublishCore *m_mqtt;
    RedisClientCore *m_redis;
};

#endif // DBTHREADCORE_H
