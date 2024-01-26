#ifndef CABELEMODEL_H
#define CABELEMODEL_H
#include "cabboxmodel.h"

class APP_DLL_EXPORT CabEleModel : public OrmEleModelBase
{
public:
    uint cabinet_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"cab_ele";}
};

QX_REGISTER_PRIMARY_KEY(CabEleModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabEleModel, qx::trait::no_base_class_defined, 1)

#endif // CABELEMODEL_H
