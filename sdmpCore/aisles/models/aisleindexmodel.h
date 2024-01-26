#ifndef AISLEINDEXMODEL_H
#define AISLEINDEXMODEL_H
#include "aislebarmodel.h"

class APP_DLL_EXPORT AisleIndexModel
{
public:
    uint id = 0;
    uint room_id=0;
    uchar pdu_bar = 0;
    uchar is_delete = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    AisleIndexModel(){}
    virtual ~AisleIndexModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"aisle_index";}
};

QX_REGISTER_PRIMARY_KEY(AisleIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleIndexModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEINDEXMODEL_H
