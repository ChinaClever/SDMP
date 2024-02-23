#ifndef CFGOBJ_H
#define CFGOBJ_H
#include <QtCore>
#include "commons/print.h"

class CfgObj
{
public:
    CfgObj(const QString& fn, QObject *parent = nullptr);
    static QString pathOfCfg(const QString& name);
    ~CfgObj();

    void writeCfg(const QMap<QString,QVariant> &map, const QString &g="");
    void writeCfg(const QString &key, const QVariant& v, const QString &g="");

    QVariantList readCfg(const QStringList &keys, const QString &g="");
    QMap<QString,QVariant> readCfg(const QMap<QString, QVariant> &keys, const QString &g="");
    QVariant readCfg(const QString &key, const QVariant &v = QVariant(), const QString &g="");

private:
    bool openCfg(const QString& fn, QObject *parent = nullptr);

private:
    QSettings *mCfgIni=nullptr;
};

#endif // CFGOBJ_H
