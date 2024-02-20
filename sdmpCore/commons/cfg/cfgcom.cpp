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
CfgCom::CfgCom(const QString &fn, QObject *parent)
    : CfgObj(fn, parent)
{
    initCfg();
    initCfgDb();
    initCfgSql();
    initCfgLog();
    initCfgRest();
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
        hda->en = readCfg(str+"hda_en", true, g).toBool();
        hda->interval = readCfg(str+"hda_interval", 15, g).toInt();
        hda->last_time = readCfg(str+"hda_last_time", t, g).toDateTime();

        ele->prefix = str +"ele_";
        ele->en = readCfg(str+"ele_en", true, g).toBool();
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
