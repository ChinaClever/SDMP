/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rackindexmodel.h"
QX_REGISTER_CPP_APP(RackIndexModel)

namespace qx
{
    template <> void register_class(QxClass<RackIndexModel> & t)
    {
        t.setName(RackIndexModel::tableName());
        t.id(&RackIndexModel::id, "id");
        t.data(&RackIndexModel::a_port, "a_port");
        t.data(&RackIndexModel::b_port, "b_port");
        t.data(&RackIndexModel::is_delete, "is_delete");
        t.data(&RackIndexModel::createtime, "create_time");
        t.data(&RackIndexModel::updatetime, "update_time");
    }
}
