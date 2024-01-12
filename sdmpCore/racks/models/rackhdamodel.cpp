/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rackhdamodel.h"
QX_REGISTER_CPP_APP(RackHdaModel)

namespace qx
{
    template <> void register_class(QxClass<RackHdaModel> & t)
    {
        t.setName(RackHdaModel::tableName());
        t.data(&RackHdaModel::tg_apparent_power, "tg_apparent_power");
        t.data(&RackHdaModel::a_apparent_power, "a_apparent_power");
        t.data(&RackHdaModel::b_apparent_power, "b_apparent_power");
        t.data(&RackHdaModel::tg_active_power, "tg_active_power");
        t.data(&RackHdaModel::a_active_power, "a_active_power");
        t.data(&RackHdaModel::b_active_power, "b_active_power");
        t.data(&RackHdaModel::createtime, "create_time");
        t.data(&RackHdaModel::rack_id, "rack_id");
        t.id(&RackHdaModel::id, "id");
    }
}
