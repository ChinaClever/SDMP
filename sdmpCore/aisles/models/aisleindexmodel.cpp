/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisleindexmodel.h"
QX_REGISTER_CPP_APP(AisleIndexModel)

namespace qx
{
    template <> void register_class(QxClass<AisleIndexModel> & t)
    {
        t.setName(AisleIndexModel::tableName());
        t.id(&AisleIndexModel::id, "id");
        t.data(&AisleIndexModel::room_id, "room_id");
        t.data(&AisleIndexModel::pdu_bar, "pdu_bar");
        t.data(&AisleIndexModel::is_delete, "is_delete");
        t.data(&AisleIndexModel::createtime, "create_time");
        t.data(&AisleIndexModel::updatetime, "update_time");
    }
}
