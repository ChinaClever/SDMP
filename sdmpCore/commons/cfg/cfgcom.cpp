/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cfgcom.h"

CfgCom::CfgCom(const QString &fn, QObject *parent)
    : CfgObj(fn, parent)
{
    initCfg();
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
