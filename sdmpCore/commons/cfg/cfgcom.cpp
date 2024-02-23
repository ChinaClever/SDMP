/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cfgcom.h"

sCfgDbItem CfgCom::mCfgDb;
sCfgSqlItem CfgCom::mCfgSql;
sCfgLogItem CfgCom::mCfgLog;
sCfgRestItem CfgCom::mCfgRest;
sCfgMqttItem CfgCom::mCfgMqtt;
sCfgPublishItem CfgCom::mCfgPublish;

CfgCom::CfgCom(const QString &fn, QObject *parent)
    : CfgObj(fn, parent)
{
    initCfg();
    initCfgDb();
    initCfgSql();
    initCfgLog();
    initCfgRest();
    initCfgMqtt();
    initCfgPublish();
}

void CfgCom::initCfg()
{

}

CfgCom *CfgCom::build(QObject *parent, const QString& fn)
{
    static CfgCom* sington = nullptr;
    if(!sington) {
        initCfg(); QString name = pathOfCfg(fn);
        sington = new CfgCom(name, parent);
    }
    return sington;
}


void CfgCom::initCfgDb()
{
    QString g = "db"; sCfgDbItem *it = &mCfgDb;
    it->driver = readCfg("driver", "QMYSQL", g).toString();
    it->prefix = readCfg("prefix", "sdmp_", g).toString();
    it->name = readCfg("name", "sdmp_db", g).toString();
    it->host = readCfg("host", "127.0.0.1", g).toString();
    it->user = readCfg("user", "root", g).toString();
    it->pwd = readCfg("pwd", "123456", g).toString();
    it->port = readCfg("port", "3306", g).toInt();
    it->en = readCfg("en", true, g).toBool();
}

void CfgCom::writeCfgDb()
{
    QString g = "db";
    sCfgDbItem *it = &mCfgDb;
    QMap<QString,QVariant> map;
    map.insert("driver", it->driver);
    map.insert("prefix", it->prefix);
    map.insert("name", it->name);
    map.insert("host", it->host);
    map.insert("user", it->user);
    map.insert("port", it->port);
    map.insert("pwd", it->pwd);
    map.insert("en", it->en);
    writeCfg(map, g);
}


void CfgCom::initCfgSql()
{
    QString g = "sql"; sCfgSqlItem *it = &mCfgSql;
    sCfgSqlUnit *hda = nullptr, *ele = nullptr;
    QString str;

    for(int i=0; i<10; ++i) {
        switch (i) {
        case 0: str = "pdu"; hda = &it->pdu_hda; ele = &it->pdu_ele; break;
        case 1: str = "room"; hda = &it->room_hda; ele = &it->room_ele; break;
        case 2: str = "aisle"; hda = &it->aisle_hda; ele = &it->aisle_ele; break;
        case 3: str = "cab"; hda = &it->cab_hda; ele = &it->cab_ele; break;
        case 4: str = "rack"; hda = &it->rack_hda; ele = &it->rack_ele; break;
        case 5: str = "bar"; hda = &it->bar_hda; ele = &it->bar_ele; break;
        case 6: str = "box"; hda = &it->box_hda; ele = &it->box_ele; break;
        default: return;
        }

        str += "_";
        hda->prefix = str +"hda_";
        QDateTime t = QDateTime::currentDateTime();
        hda->en = readCfg(str+"hda_en", true, g).toBool();  //////////=======
        hda->interval = readCfg(str+"hda_interval", 120, g).toInt();
        hda->last_time = readCfg(str+"hda_last_time", t, g).toDateTime();

        ele->prefix = str +"ele_";
        ele->en = readCfg(str+"ele_en", true, g).toBool(); /////////========
        ele->interval = readCfg(str+"ele_interval", 12, g).toInt();
        ele->last_time = readCfg(str+"ele_last_time", t, g).toDateTime();
    }
}

void CfgCom::initCfgLog()
{
    QString g = "log"; sCfgLogItem *it = &mCfgLog;
    it->en = readCfg("en", true, g).toBool();
    it->url = readCfg("url", "", g).toString();
}

void CfgCom::initCfgRest()
{
    QString g = "rest"; sCfgRestItem *it = &mCfgRest;
    it->http.en = readCfg("http_en", true, g).toBool();
    it->http.acl = readCfg("http_acl", 1, g).toInt();
    it->http.port = readCfg("http_port", 43796, g).toInt();
    it->http.url = readCfg("http_url", "0.0.0.0", g).toString();
    it->http.prefix = "http_";

    it->https.en = readCfg("https_en", true, g).toBool();
    it->https.acl = readCfg("https_acl", 1, g).toInt();
    it->https.port = readCfg("https_port", 43795, g).toInt();
    it->https.url = readCfg("https_url", "0.0.0.0", g).toString();
    it->https.prefix = "https_";
}


void CfgCom::initCfgMqtt()
{
    QString prefix = "mqtt"; QString key;
    sCfgMqttItem *cfg = &(mCfgMqtt);
    for(int i=1; i<11; ++i) {
        switch (i) {
        case 1: key = "type"; cfg->type = readCfg(key, 0, prefix).toInt(); break;
        case 2: key = "url"; cfg->url = readCfg(key, "", prefix).toString(); break;
        case 3: key = "port"; cfg->port = readCfg(key, 1883, prefix).toInt(); break;
        case 4: key = "path"; cfg->path = readCfg(key, "/mqtt", prefix).toString(); break;
        case 5: key = "clientId"; cfg->clientId = readCfg(key, "clientId", prefix).toString(); break;
        case 6: key = "usr"; cfg->usr = readCfg(key, "", prefix).toByteArray(); break;
        case 7: key = "pwd"; cfg->pwd = readCfg(key, "", prefix).toByteArray(); break;
        case 8: key = "keepAlive"; cfg->keepAlive = readCfg(key, 60, prefix).toInt();break;
        case 9: key = "qos"; cfg->qos = readCfg(key, 0, prefix).toInt(); break;
        case 10: key = "sec"; cfg->sec = readCfg(key, 10, prefix).toInt(); break;
        default: key.clear(); break;
        }
    }
}

void CfgCom::writeCfgMqtt()
{
    QString g = "mqtt";
    sCfgMqttItem *it = &mCfgMqtt;
    QMap<QString,QVariant> map;
    map.insert("type", it->type);
    map.insert("url", it->url);
    map.insert("port", it->port);
    map.insert("path", it->path);
    map.insert("usr", it->usr);
    map.insert("pwd", it->pwd);
    map.insert("qos", it->qos);
    map.insert("keepAlive", it->keepAlive);
    map.insert("clientId", it->clientId);
    writeCfg(map, g);
}


void CfgCom::initCfgPublish()
{
    QString str;
    QString g = "publish";
    sCfgMqttUnit *unit = nullptr;
    sCfgPublishItem *it = &mCfgPublish;

    for(int i=0; i<10; ++i) {
        switch (i) {
        case 0: str = "pdu"; unit = &it->pdu; break;
        case 1: str = "room"; unit = &it->room; break;
        case 2: str = "aisle"; unit = &it->aisle; break;
        case 3: str = "cabinet"; unit = &it->cab; break;
        case 4: str = "rack"; unit = &it->rack; break;
        case 5: str = "busbar"; unit = &it->busbar; break;
        default: return;
        }

        unit->topic = readCfg(str+"_topic", str+"MetaTopic", g).toString();
        str += "_"; unit->prefix = str;
        QDateTime t = QDateTime::currentDateTime();
        unit->en = readCfg(str+"en", true, g).toBool();///////=======
        unit->interval = readCfg(str+"interval", 15, g).toInt();
        unit->last_time = readCfg(str+"last_time", t, g).toDateTime();
    }
}
