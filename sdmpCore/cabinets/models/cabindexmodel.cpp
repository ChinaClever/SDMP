/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cabindexmodel.h"
QX_REGISTER_CPP_APP(CabIndexModel)

namespace qx
{
    template <> void register_class(QxClass<CabIndexModel> & t)
    {
        t.setName(CabIndexModel::tableName());
        t.id(&CabIndexModel::id, "id");
        t.data(&CabIndexModel::name, "name");
        t.data(&CabIndexModel::room_id, "room_id");
        t.data(&CabIndexModel::aisle_id, "aisle_id");
        t.data(&CabIndexModel::pdu_box, "pdu_box");
        t.data(&CabIndexModel::is_delete, "is_delete");
        t.data(&CabIndexModel::is_disabled, "is_disabled");
        t.data(&CabIndexModel::pow_capacity, "pow_capacity");
        t.data(&CabIndexModel::createtime, "create_time");
        t.data(&CabIndexModel::updatetime, "update_time");
    }
}
