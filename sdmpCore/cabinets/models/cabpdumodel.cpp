/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cabpdumodel.h"
QX_REGISTER_CPP_APP(CabPduModel)

namespace qx
{
    template <> void register_class(QxClass<CabPduModel> & t)
    {
        t.setName(CabPduModel::tableName());
        t.id(&CabPduModel::id, "id");
        t.data(&CabPduModel::a_pdu_id, "a_pdu_id");
        t.data(&CabPduModel::b_pdu_id, "b_pdu_id");
        t.data(&CabPduModel::cabinet_id, "cabinet_id");
        t.data(&CabPduModel::createtime, "create_time");
        t.data(&CabPduModel::updatetime, "update_time");
    }
}
