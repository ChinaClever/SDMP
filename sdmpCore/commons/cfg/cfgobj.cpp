/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cfgobj.h"


CfgObj::CfgObj(const QString &fn, QObject *parent)
{
    if(!mCfgIni) openCfg(fn, parent);
}

CfgObj::~CfgObj()
{
    if(mCfgIni) delete mCfgIni;
}


/***
  * 获取程序数据目录
  */
QString CfgObj::pathOfCfg(const QString& name)
{
#if (QT_VERSION > QT_VERSION_CHECK(5,13,0))
    QDir dataDir(QDir::home());  // QCoreApplication::applicationDirPath() QDir::home()
    QString dirName = "." + QCoreApplication::organizationName();
    if(!dataDir.exists(dirName)) {dataDir.mkdir(dirName);} dataDir.cd(dirName);

    dirName = QCoreApplication::applicationName();
    if(!dataDir.exists(dirName)) {dataDir.mkdir(dirName);} dataDir.cd(dirName);
#else
    QDir dataDir("/usr/data/clever/"); QString dirName = "cfg";
    if(!dataDir.exists(dirName)) {dataDir.mkdir(dirName);} dataDir.cd(dirName);
#endif
    cout << dataDir.absoluteFilePath(name);

    return dataDir.absoluteFilePath(name);
}

/**
 * 功 能：打开系统配置文件
 * 开发人员：Lzy     2016 - 七夕
 */
bool CfgObj::openCfg(const QString& fn, QObject *parent)
{
    bool ret = QFileInfo::exists(fn);
    if(mCfgIni == nullptr) {
        mCfgIni = new QSettings(fn, QSettings::IniFormat, parent);
        //mCfgIni->setIniCodec(QTextCodec::codecForName("utf-8"));
    }

    return ret;
}

void CfgObj::writeCfg(const QMap<QString,QVariant> &map, const QString &g)
{
    mCfgIni->beginGroup(g);
    for(auto &it: map.toStdMap()) {
        mCfgIni->setValue(it.first, it.second);
    } mCfgIni->endGroup();
    mCfgIni->sync();
}

/**
 * 功 能：参数写入配置文件
 * 开发人员：Lzy     2016 - 七夕
 */
void CfgObj::writeCfg(const QString& key, const QVariant &v, const QString& g)
{
    QMap<QString,QVariant> map;
    map.insert(key, v); writeCfg(map, g);   /*将配置项和对应的参数插入到map中，然后写入配置文件*/
}

QVariantList CfgObj::readCfg(const QStringList &keys, const QString &g)
{
    QVariantList res; mCfgIni->beginGroup(g);
    foreach(auto &it, keys) res << mCfgIni->value(it,"");
    mCfgIni->endGroup(); return res;
}

QMap<QString,QVariant> CfgObj::readCfg(const QMap<QString,QVariant> &keys, const QString &g)
{
    QMap<QString,QVariant> res; mCfgIni->beginGroup(g);
    for(auto &it: keys.toStdMap()){
        res.insert(it.first, mCfgIni->value(it.first, it.second));
    } mCfgIni->endGroup(); return res;
}

QVariant CfgObj::readCfg(const QString &key, const QVariant &v, const QString& g)
{
    mCfgIni->beginGroup(g);
    QVariant ret = mCfgIni->value(key, v);
    mCfgIni->endGroup();

    return ret;
}
