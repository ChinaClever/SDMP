/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cabelemodel.h"
QX_REGISTER_CPP_APP(CabEleModel)

namespace qx
{
    template <> void register_class(QxClass<CabEleModel> & t)
    {
        t.setName(CabEleModel::tableName());
        t.id(&CabEleModel::id, "id");
        t.data(&CabEleModel::tg_ele, "tg_ele");
        t.data(&CabEleModel::a_ele, "a_ele");
        t.data(&CabEleModel::b_ele, "b_ele");
        t.data(&CabEleModel::createdate, "create_date");
        t.data(&CabEleModel::createtime, "create_time");
    }
}
