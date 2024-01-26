#ifndef CABBOXMODEL_H
#define CABBOXMODEL_H
#include "cabpdumodel.h"

class APP_DLL_EXPORT CabBoxModel
{
public:
    uint id = 0;
    uint cabinet_id=0;
    uint a_box_id = 0;
    uchar a_outlet_id = 0;
    uint b_box_id = 0;
    uchar b_outlet_id = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~CabBoxModel(){} CabBoxModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"cab_box";}
};

QX_REGISTER_PRIMARY_KEY(CabBoxModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabBoxModel, qx::trait::no_base_class_defined, 1)

#endif // CABBOXMODEL_H
