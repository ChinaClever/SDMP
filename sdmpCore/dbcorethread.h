#ifndef DBCORETHREAD_H
#define DBCORETHREAD_H

#include "cabinets/sqls/cab_hdasql.h"

class DbCoreThread : public QThread
{
    Q_OBJECT
public:
    explicit DbCoreThread(QObject *parent = nullptr);

    void initFun();
protected:
    void run();
    void syncWork();
    void hdaWork();
    void eleWork();
    void alarmWork();
    void workDown();

private slots:
    void onTimeout() {start();}

private:
    uint mCnt = 1;
    bool isRun = false;
    QTimer *mTimer = nullptr;
};

#endif // DBCORETHREAD_H
