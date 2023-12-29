/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdualarmmodel.h"
QX_REGISTER_CPP_APP(PduAlarmModel)

namespace qx
{
    template <> void register_class(QxClass<PduAlarmModel> & t)
    {
        t.setName(PduAlarmModel::tableName());
        t.id(&PduAlarmModel::id, "id");
        t.data(&PduAlarmModel::pdu_id, "pdu_id");
        t.data(&PduAlarmModel::status, "alarm_status");
        t.data(&PduAlarmModel::content, "alarm_content");
        t.data(&PduAlarmModel::createtime, "createtime");
    }
}
