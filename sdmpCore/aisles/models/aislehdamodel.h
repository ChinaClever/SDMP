#ifndef AISLEHDAMODEL_H
#define AISLEHDAMODEL_H
#include "aisleelemodel.h"

class APP_DLL_EXPORT AisleHdaModel : public OrmHdaModelBase
{
public:
    uint aisle_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"aisle_hda";}
};

QX_REGISTER_PRIMARY_KEY(AisleHdaModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleHdaModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEHDAMODEL_H
