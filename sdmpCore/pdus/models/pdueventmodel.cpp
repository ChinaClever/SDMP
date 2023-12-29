/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdueventmodel.h"
QX_REGISTER_CPP_APP(PduEventModel)

namespace qx
{
    template <> void register_class(QxClass<PduEventModel> & t)
    {
        t.setName(PduEventModel::tableName());
        t.id(&PduEventModel::id, "id");
        t.data(&PduEventModel::pdu_id, "pdu_id");
        t.data(&PduEventModel::type, "event_type");
        t.data(&PduEventModel::content, "event_content");
        t.data(&PduEventModel::createtime, "createtime");
    }
}
