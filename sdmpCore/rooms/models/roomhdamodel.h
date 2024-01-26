#ifndef ROOMHDAMODEL_H
#define ROOMHDAMODEL_H
#include "roomelemodel.h"

class APP_DLL_EXPORT RoomHdaModel  : public OrmHdaModelBase
{
public:
    uint room_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"room_hda";}
};

QX_REGISTER_PRIMARY_KEY(RoomHdaModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(RoomHdaModel, qx::trait::no_base_class_defined, 1)

#endif // ROOMHDAMODEL_H
