#ifndef CFGCOM_H
#define CFGCOM_H
#include "cfgobj.h"
#define CFG_FN "cfg.ini"



class CfgCom : public CfgObj
{
    CfgCom(const QString& fn, QObject *parent = nullptr);
public:
    static CfgCom* bulid(QObject *parent = nullptr, const QString& fn=CFG_FN);

private:
    static void initCfg();
};

#endif // CFGCOM_H
