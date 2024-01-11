/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "roomindexmodel.h"
QX_REGISTER_CPP_APP(RoomIndexModel)

namespace qx
{
    template <> void register_class(QxClass<RoomIndexModel> & t)
    {
        t.setName(RoomIndexModel::tableName());
        t.id(&RoomIndexModel::id, "id");
        t.data(&RoomIndexModel::is_delete, "is_delete");
        t.data(&RoomIndexModel::power_capacity, "power_capacity");
        t.data(&RoomIndexModel::createtime, "create_time");
        t.data(&RoomIndexModel::updatetime, "update_time");
    }
}
