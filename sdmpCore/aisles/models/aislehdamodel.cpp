/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aislehdamodel.h"
QX_REGISTER_CPP_APP(AisleHdaModel)

namespace qx
{
    template <> void register_class(QxClass<AisleHdaModel> & t)
    {
        t.setName(AisleHdaModel::tableName());
        t.data(&AisleHdaModel::tg_apparent_power, "tg_apparent_power");
        t.data(&AisleHdaModel::a_apparent_power, "a_apparent_power");
        t.data(&AisleHdaModel::b_apparent_power, "b_apparent_power");
        t.data(&AisleHdaModel::tg_active_power, "tg_active_power");
        t.data(&AisleHdaModel::a_active_power, "a_active_power");
        t.data(&AisleHdaModel::b_active_power, "b_active_power");
        t.data(&AisleHdaModel::createtime, "create_time");
        t.data(&AisleHdaModel::aisle_id, "aisle_id");
        t.id(&AisleHdaModel::id, "id");
    }
}
