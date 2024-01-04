/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdulogmodel.h"
QX_REGISTER_CPP_APP(PduLogModel)

namespace qx
{
    template <> void register_class(QxClass<PduLogModel> & t)
    {
        t.setName(PduLogModel::tableName());
        t.id(&PduLogModel::id, "id");
        t.data(&PduLogModel::pdu_id, "pdu_id");
        t.data(&PduLogModel::content, "content");
        t.data(&PduLogModel::state_type, "state_type");
        t.data(&PduLogModel::alarm_event, "alarm_event");
        t.data(&PduLogModel::createtime, "create_time");
    }
}
