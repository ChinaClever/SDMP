/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aislebarmodel.h"
QX_REGISTER_CPP_APP(AisleBarModel)

namespace qx
{
    template <> void register_class(QxClass<AisleBarModel> & t)
    {
        t.setName(AisleBarModel::tableName());
        t.id(&AisleBarModel::id, "id");
        t.data(&AisleBarModel::aisle_id, "aisle_id");
        t.data(&AisleBarModel::a_bar_id, "a_bar_id");
        t.data(&AisleBarModel::b_bar_id, "b_bar_id");
        t.data(&AisleBarModel::createtime, "create_time");
        t.data(&AisleBarModel::updatetime, "update_time");
    }
}
