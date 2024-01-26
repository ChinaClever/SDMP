#ifndef CABHDAMODEL_H
#define CABHDAMODEL_H
#include "cabelemodel.h"

class APP_DLL_EXPORT CabHdaModel : public OrmHdaModelBase
{
public:
    uint cabinet_id=0;
    static QString tableName() {return  CfgCom::db_prefix()+"cab_hda";}
};

QX_REGISTER_PRIMARY_KEY(CabHdaModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabHdaModel, qx::trait::no_base_class_defined, 1)

#endif // CABHDAMODEL_H
