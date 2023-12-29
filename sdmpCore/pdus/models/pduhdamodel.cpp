/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduhdamodel.h"
QX_REGISTER_CPP_APP(PduHdaModel)

namespace qx
{
    template <> void register_class(QxClass<PduHdaModel> & t)
    {
        t.setName(PduHdaModel::tableName());
        t.id(&PduHdaModel::id, "id");
        t.data(&PduHdaModel::pdu_id, "pdu_id");
        t.data(&PduHdaModel::type, "type");
        t.data(&PduHdaModel::topic, "topic");
        t.data(&PduHdaModel::indexes, "indexes");
        t.data(&PduHdaModel::value, "value");
        t.data(&PduHdaModel::createtime, "createtime");
    }
}
