#ifndef DBTHREADCORE_H
#define DBTHREADCORE_H
#include "httpservercore.h"
// #include "racks/sqls/rack_hdasql.h"

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
    uint mCnt = 1;
    bool isRun = false;
    bool isWrite = false;
    QStringList mWriteLst;
    QTimer *mTimer = nullptr;
    MqttPublishCore *m_mqtt;
};

#endif // DBTHREADCORE_H
