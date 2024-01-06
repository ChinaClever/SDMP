/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cabboxmodel.h"
QX_REGISTER_CPP_APP(CabBoxModel)

namespace qx
{
    template <> void register_class(QxClass<CabBoxModel> & t)
    {
        t.setName(CabBoxModel::tableName());
        t.id(&CabBoxModel::id, "id");
        t.data(&CabBoxModel::a_box_id, "a_box_id");
        t.data(&CabBoxModel::b_box_id, "b_box_id");
        t.data(&CabBoxModel::cabinet_id, "cabinet_id");
        t.data(&CabBoxModel::a_outlet_id, "a_outlet_id");
        t.data(&CabBoxModel::b_outlet_id, "b_outlet_id");
        t.data(&CabBoxModel::createtime, "create_time");
        t.data(&CabBoxModel::updatetime, "update_time");
    }
}
