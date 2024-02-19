#ifndef DBCORETHREAD_H
#define DBCORETHREAD_H
#include "cabinets/network/cab_httpserver.h"
#include "racks/sqls/rack_hdasql.h"

class DbCoreThread : public Cab_HttpServer
{
    Q_OBJECT
    explicit DbCoreThread(QObject *parent = nullptr);
public:
    static DbCoreThread *build(QObject *parent = nullptr);
    bool writing(){return isWrite;}
    QStringList writeMsg();
    ~DbCoreThread();
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
};

#endif // DBCORETHREAD_H
