#ifndef ROOMHDAMODEL_H
#define ROOMHDAMODEL_H
#include "roomelemodel.h"

class APP_DLL_EXPORT RoomHdaModel
{
public:
    uint id = 0;
    uint room_id=0;
    double tg_apparent_power = 0;
    double a_apparent_power = 0;
    double b_apparent_power = 0;
    double tg_active_power = 0;
    double a_active_power = 0;
    double b_active_power = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    RoomHdaModel(){}
    virtual ~RoomHdaModel(){}
    static QString tableName() {return "room_hda";}
};

QX_REGISTER_PRIMARY_KEY(RoomHdaModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RoomHdaModel, qx::trait::no_base_class_defined, 1)

#endif // ROOMHDAMODEL_H
