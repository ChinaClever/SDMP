/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdueventsql.h"

PduEventSql::PduEventSql()
{
    // test();
}

PduEventSql *PduEventSql::bulid()
{
    static PduEventSql* sington = nullptr;
    if(!sington) sington = new PduEventSql();
    return sington;
}


void PduEventSql::append(uint pdu_id, const QString &type, const QString &content)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->content = content;
    mLstIts.append(it);
}


void PduEventSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, "1","2");
    }insert();
}

