#ifndef RACKHDAMODEL_H
#define RACKHDAMODEL_H
#include "rackelemodel.h"

class APP_DLL_EXPORT RackHdaModel : public OrmHdaModelBase
{
public:
    uint rack_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"rack_hda";}
};

QX_REGISTER_PRIMARY_KEY(RackHdaModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(RackHdaModel, qx::trait::no_base_class_defined, 1)

#endif // RACKHDAMODEL_H
