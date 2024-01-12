/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rackelemodel.h"
QX_REGISTER_CPP_APP(RackEleModel)

namespace qx
{
    template <> void register_class(QxClass<RackEleModel> & t)
    {
        t.setName(RackEleModel::tableName());
        t.id(&RackEleModel::id, "id");
        t.data(&RackEleModel::a_ele, "a_ele");
        t.data(&RackEleModel::b_ele, "b_ele");
        t.data(&RackEleModel::tg_ele, "tg_ele");
        t.data(&RackEleModel::rack_id, "rack_id");
        t.data(&RackEleModel::createdate, "create_date");
        t.data(&RackEleModel::createtime, "create_time");
    }
}
