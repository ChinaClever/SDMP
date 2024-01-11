/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "roomhdamodel.h"
QX_REGISTER_CPP_APP(RoomHdaModel)

namespace qx
{
    template <> void register_class(QxClass<RoomHdaModel> & t)
    {
        t.setName(RoomHdaModel::tableName());
        t.data(&RoomHdaModel::tg_apparent_power, "tg_apparent_power");
        t.data(&RoomHdaModel::a_apparent_power, "a_apparent_power");
        t.data(&RoomHdaModel::b_apparent_power, "b_apparent_power");
        t.data(&RoomHdaModel::tg_active_power, "tg_active_power");
        t.data(&RoomHdaModel::a_active_power, "a_active_power");
        t.data(&RoomHdaModel::b_active_power, "b_active_power");
        t.data(&RoomHdaModel::createtime, "create_time");
        t.data(&RoomHdaModel::room_id, "room_id");
        t.id(&RoomHdaModel::id, "id");
    }
}
