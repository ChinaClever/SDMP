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
    int port = 3306;
    bool en = true;
};

struct sCfgSqlUnit
{
    bool en = true;
    QString prefix;
    int interval = 10;
    QDateTime last_time;
};


struct sCfgSqlItem
{
    sCfgSqlUnit pdu_hda;
    sCfgSqlUnit pdu_ele;

    sCfgSqlUnit room_hda;
    sCfgSqlUnit room_ele;

    sCfgSqlUnit aisle_hda;
    sCfgSqlUnit aisle_ele;

    sCfgSqlUnit cab_hda;
    sCfgSqlUnit cab_ele;

    sCfgSqlUnit rack_hda;
    sCfgSqlUnit rack_ele;

    sCfgSqlUnit bar_hda;
    sCfgSqlUnit bar_ele;

    sCfgSqlUnit box_hda;
    sCfgSqlUnit box_ele;
};

struct sCfgRestUnit
{
    bool en = true;
    int port = 43796;
    int acl = 1;
    QString url = "0.0.0.0";
    QString prefix;
};

struct sCfgRestItem
{
    sCfgRestUnit http;
    sCfgRestUnit https;
};


struct sCfgMqttItem {
    sCfgMqttItem():type(2), url("192.168.1.2"), port(8883), path("/mqtt"),
        clientId("clientId"), isConnected(false), keepAlive(60), qos(0), sec(5){}

    int type; // 1 mqtt 2 mqtts 3 ws 4 wss
    QString url;
    quint16 port;
    QString path;
    QString clientId;
    QByteArray usr, pwd;
    bool isConnected;
    int keepAlive;
    int qos;
    int sec;
};

struct sCfgMqttUnit
{
    bool en = true;
    QString topic;
    QString prefix;
    int interval = 10;
    QDateTime last_time;
};

struct sCfgPublishItem
{
    sCfgMqttUnit pdu;
    sCfgMqttUnit room;
    sCfgMqttUnit aisle;
    sCfgMqttUnit cab;
    sCfgMqttUnit rack;
    sCfgMqttUnit busbar;
};


struct sCfgRedisUnit
{
    bool en = true;
    QString key;
    QString prefix;
    int interval = 10;
    QDateTime last_time;
};

struct sCfgRedisItem
{
    bool en = true;
    int db = 0;
    int port = 6379;
    QString pwd, host = "localhost";

    sCfgRedisUnit pdu;
    sCfgRedisUnit room;
    sCfgRedisUnit aisle;
    sCfgRedisUnit cab;
    sCfgRedisUnit rack;
    sCfgRedisUnit busbar;
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
    static sCfgRestItem mCfgRest;
    static sCfgLogItem mCfgLog;
    static sCfgMqttItem mCfgMqtt;
    static sCfgRedisItem mCfgRedis;
    static sCfgPublishItem mCfgPublish;

    void writeCfgDb();
    void writeCfgMqtt();
    void writeCfgRedis();

private:
    static void initCfg();    
    void initCfgDb();
    void initCfgSql();
    void initCfgLog();
    void initCfgRest();
    void initCfgMqtt();
    void initCfgPublish();
    void initCfgRedis();
};

#endif // CFGCOM_H
