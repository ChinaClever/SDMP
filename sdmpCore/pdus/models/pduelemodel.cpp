/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduelemodel.h"
QX_REGISTER_CPP_APP(PduEleModel)

namespace qx
{
    template <> void register_class(QxClass<PduEleModel> & t)
    {
        t.setName(PduEleModel::tableName());
        t.id(&PduEleModel::id, "id");
        t.data(&PduEleModel::pdu_id, "pdu_id");
        t.data(&PduEleModel::type, "type");
        t.data(&PduEleModel::indexes, "indexes");
        t.data(&PduEleModel::value, "value");
        t.data(&PduEleModel::createdate, "createdate");
        t.data(&PduEleModel::createtime, "createtime");
    }
}
