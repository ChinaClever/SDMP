#ifndef ROOMELEMODEL_H
#define ROOMELEMODEL_H
#include "roomindexmodel.h"

class APP_DLL_EXPORT RoomEleModel
{
public:
    uint id = 0;
    uint room_id=0;
    double tg_ele = 0;
    double a_ele = 0;
    double b_ele = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();

    RoomEleModel(){}
    virtual ~RoomEleModel(){}
    static QString tableName() {return "room_ele";}
};

QX_REGISTER_PRIMARY_KEY(RoomEleModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RoomEleModel, qx::trait::no_base_class_defined, 1)

#endif // ROOMELEMODEL_H
