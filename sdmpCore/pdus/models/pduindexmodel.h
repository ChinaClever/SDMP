#ifndef PDUINDEXMODEL_H
#define PDUINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT PduIndexModel
{
public:
    uint id = 0;
    QString key,ip;
    uchar is_delete = 0;
    uchar cascade_num = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~PduIndexModel(){} PduIndexModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"pdu_index";}
};

QX_REGISTER_PRIMARY_KEY(PduIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduIndexModel, qx::trait::no_base_class_defined, 1)

#endif // PDUINDEXMODEL_H
