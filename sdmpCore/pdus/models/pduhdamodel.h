#ifndef PDUHDAMODEL_H
#define PDUHDAMODEL_H
#include "pduelemodel.h"

class APP_DLL_EXPORT PduHdaModel
{
public:
    quint64 id = 0;
    uint pdu_id = 0;
    uchar type = 0;
    uchar topic = 0;
    uchar indexes = 0;
    double value = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    virtual ~PduHdaModel(){} PduHdaModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"pdu_hda";}
};

QX_REGISTER_PRIMARY_KEY(PduHdaModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduHdaModel, qx::trait::no_base_class_defined, 1)

#endif // PDUHDAMODEL_H
