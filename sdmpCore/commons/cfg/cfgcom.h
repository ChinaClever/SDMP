#ifndef CFGCOM_H
#define CFGCOM_H
#include "cfgobj.h"
#define CFG_FN "cfg.ini"

struct sCfgDbItem
{
    QString driver = "QMYSQL";
    QString name = "sdmp_db";
    QString host = "127.0.0.1";
    QString user = "root";
    QString pwd = "123456";
    QString prefix = "sdmp_";
};

struct sCfgSqlItem
{
    bool hda_en = true;
    int hda_interval = 10; // 分钟
    QDateTime hda_last_time; // 上一次记录时间

    bool ele_en = true;
    int ele_interval = 12; // 小时
    QDateTime ele_last_time; // 上一次记录时间
};

struct sCfgLogItem
{
    bool en = true;
    QString url = "";
};

class CfgCom : public CfgObj
{
    CfgCom(const QString& fn, QObject *parent = nullptr);
public:
    static CfgCom* build(QObject *parent = nullptr, const QString& fn=CFG_FN);
    static QString db_prefix() {return mCfgDb.prefix;}

    static sCfgDbItem mCfgDb;
    static sCfgSqlItem mCfgSql;
    static sCfgLogItem mCfgLog;

private:
    static void initCfg();    
    void initCfgDb();
    void initCfgSql();
    void initCfgLog();
};

#endif // CFGCOM_H
