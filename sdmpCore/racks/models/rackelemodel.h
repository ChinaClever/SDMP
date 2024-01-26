#ifndef RACKELEMODEL_H
#define RACKELEMODEL_H
#include "rackindexmodel.h"

class APP_DLL_EXPORT RackEleModel : public OrmEleModelBase
{
public:
    uint rack_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"rack_ele";}
};

QX_REGISTER_PRIMARY_KEY(RackEleModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(RackEleModel, qx::trait::no_base_class_defined, 1)


#endif // RACKELEMODEL_H
