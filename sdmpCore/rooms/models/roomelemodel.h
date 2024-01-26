#ifndef ROOMELEMODEL_H
#define ROOMELEMODEL_H
#include "roomindexmodel.h"

class APP_DLL_EXPORT RoomEleModel : public OrmEleModelBase
{
public:
    uint room_id=0;
    static QString tableName() {return CfgCom::db_prefix()+"room_ele";}
};

QX_REGISTER_PRIMARY_KEY(RoomEleModel, quint64)  // 定义主键的类型
QX_REGISTER_HPP_APP(RoomEleModel, qx::trait::no_base_class_defined, 1)

#endif // ROOMELEMODEL_H
