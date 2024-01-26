#ifndef AISLEELEMODEL_H
#define AISLEELEMODEL_H
#include "aisleindexmodel.h"

class APP_DLL_EXPORT AisleEleModel : public OrmEleModelBase
{
public:
    uint aisle_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"aisle_ele";}
};

QX_REGISTER_PRIMARY_KEY(AisleEleModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleEleModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEELEMODEL_H
