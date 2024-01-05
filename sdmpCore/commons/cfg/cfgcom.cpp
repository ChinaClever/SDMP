/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cfgcom.h"


sCfgDbItem CfgCom::mCfgDb;
sCfgSqlItem CfgCom::mCfgSql;
sCfgLogItem CfgCom::mCfgLog;

CfgCom::CfgCom(const QString &fn, QObject *parent)
    : CfgObj(fn, parent)
{
    initCfg();
    initCfgDb();
    initCfgSql();
    initCfgLog();
}

void CfgCom::initCfg()
{
    QCoreApplication::setOrganizationName("CLEVER");
    QCoreApplication::setOrganizationDomain("clever.com");
    QCoreApplication::setApplicationName("sdmp");
}

CfgCom *CfgCom::bulid(QObject *parent, const QString& fn)
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
    it->prefix = readCfg("prefix", "sdmp", g).toString();
    it->name = readCfg("name", "sdmp_db", g).toString();
    it->host = readCfg("host", "127.0.0.1", g).toString();
    it->user = readCfg("user", "root", g).toString();
    it->pwd = readCfg("pwd", "123456", g).toString();
}

void CfgCom::initCfgSql()
{
    QString g = "sql"; sCfgSqlItem *it = &mCfgSql;
    it->hda_en = readCfg("hda_en", true, g).toBool();
    it->hda_interval = readCfg("hda_interval", 10, g).toInt();
    it->hda_last_time = readCfg("hda_last_time", QDateTime::currentDateTime(), g).toDateTime();

    it->ele_en = readCfg("ele_en", true, g).toBool();
    it->ele_interval = readCfg("ele_interval", 12, g).toInt();
    it->ele_last_time = readCfg("ele_last_time", QDateTime::currentDateTime(), g).toDateTime();
}

void CfgCom::initCfgLog()
{
    QString g = "log"; sCfgLogItem *it = &mCfgLog;
    it->en = readCfg("en", true, g).toBool();
    it->url = readCfg("url", "", g).toString();
}
