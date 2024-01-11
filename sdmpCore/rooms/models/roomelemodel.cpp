/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "roomelemodel.h"
QX_REGISTER_CPP_APP(RoomEleModel)

namespace qx
{
    template <> void register_class(QxClass<RoomEleModel> & t)
    {
        t.setName(RoomEleModel::tableName());
        t.id(&RoomEleModel::id, "id");
        t.data(&RoomEleModel::a_ele, "a_ele");
        t.data(&RoomEleModel::b_ele, "b_ele");
        t.data(&RoomEleModel::tg_ele, "tg_ele");
        t.data(&RoomEleModel::room_id, "room_id");
        t.data(&RoomEleModel::createdate, "create_date");
        t.data(&RoomEleModel::createtime, "create_time");
    }
}
