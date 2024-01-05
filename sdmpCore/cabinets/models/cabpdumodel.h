#ifndef CABPDUMODEL_H
#define CABPDUMODEL_H
#include "cab_indexsql.h"

class APP_DLL_EXPORT CabPduModel
{
public:
    uint id = 0;
    uint cabinet_id=0;
    uint a_pdu_id = 0;
    uint b_pdu_id = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    CabPduModel(){}
    virtual ~CabPduModel(){}
    static QString tableName() {return "cab_pdu";}
};

QX_REGISTER_PRIMARY_KEY(CabPduModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabPduModel, qx::trait::no_base_class_defined, 1)

#endif // CABPDUMODEL_H
