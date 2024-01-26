#ifndef ROOMINDEXMODEL_H
#define ROOMINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT RoomIndexModel
{
public:
    uint id = 0;
    uchar is_delete = 0;
    double power_capacity=0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~RoomIndexModel(){} RoomIndexModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"room_index";}
};

QX_REGISTER_PRIMARY_KEY(RoomIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RoomIndexModel, qx::trait::no_base_class_defined, 1)

#endif // ROOMINDEXMODEL_H
