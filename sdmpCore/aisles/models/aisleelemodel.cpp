/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisleelemodel.h"
QX_REGISTER_CPP_APP(AisleEleModel)

namespace qx
{
    template <> void register_class(QxClass<AisleEleModel> & t)
    {
        t.setName(AisleEleModel::tableName());
        t.id(&AisleEleModel::id, "id");
        t.data(&AisleEleModel::a_ele, "a_ele");
        t.data(&AisleEleModel::b_ele, "b_ele");
        t.data(&AisleEleModel::tg_ele, "tg_ele");
        t.data(&AisleEleModel::aisle_id, "aisle_id");
        t.data(&AisleEleModel::createdate, "create_date");
        t.data(&AisleEleModel::createtime, "create_time");
    }
}
