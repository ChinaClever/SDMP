/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduindexmodel.h"
QX_REGISTER_CPP_APP(PduIndexModel)

namespace qx
{
    template <> void register_class(QxClass<PduIndexModel> & t)
    {
        t.setName(PduIndexModel::tableName());
        t.id(&PduIndexModel::id, "id");
        t.data(&PduIndexModel::ip, "ip_addr");
        t.data(&PduIndexModel::key, "dev_key");
        t.data(&PduIndexModel::is_delete, "is_delete");
        t.data(&PduIndexModel::cascade_num, "cascade_num");
        t.data(&PduIndexModel::createtime, "create_time");
        t.data(&PduIndexModel::updatetime, "update_time");
    }
}

