/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cabhdamodel.h"
QX_REGISTER_CPP_APP(CabHdaModel)

namespace qx
{
    template <> void register_class(QxClass<CabHdaModel> & t)
    {
        t.setName(CabHdaModel::tableName());
        t.data(&CabHdaModel::tg_apparent_power, "tg_apparent_power");
        t.data(&CabHdaModel::a_apparent_power, "a_apparent_power");
        t.data(&CabHdaModel::b_apparent_power, "b_apparent_power");
        t.data(&CabHdaModel::tg_active_power, "tg_active_power");
        t.data(&CabHdaModel::a_active_power, "a_active_power");
        t.data(&CabHdaModel::b_active_power, "b_active_power");
        t.data(&CabHdaModel::createtime, "create_time");
        t.data(&CabHdaModel::cabinet_id, "cabinet_id");
        t.id(&CabHdaModel::id, "id");
    }
}
