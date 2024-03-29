#ifndef CABPDUMODEL_H
#define CABPDUMODEL_H
#include "cabindexmodel.h"

class APP_DLL_EXPORT CabPduModel
{
public:
    uint id = 0;
    uint cabinet_id=0;
    uchar a_cas_id = 0;
    uchar b_cas_id = 0;
    QString a_pdu_ip, b_pdu_ip;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~CabPduModel(){} CabPduModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"cab_pdu";}
};

QX_REGISTER_PRIMARY_KEY(CabPduModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabPduModel, qx::trait::no_base_class_defined, 1)

#endif // CABPDUMODEL_H
