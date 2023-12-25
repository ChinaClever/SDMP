/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduindexmodel.h"
#include <QxOrm_Impl.h>

QX_REGISTER_CPP_APP(PduIndexModel)

namespace qx
{
    template <> void register_class(QxClass<PduIndexModel> & t)
    {
        t.setName(PduIndexModel::tableName());
        t.id(&PduIndexModel::id, "id");
        t.data(&PduIndexModel::name, "name");
        t.data(&PduIndexModel::age, "age");
    }
}

