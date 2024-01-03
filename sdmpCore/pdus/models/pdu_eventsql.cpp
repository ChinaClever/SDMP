/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_eventsql.h"

Pdu_EventSql::Pdu_EventSql()
{
    // test();
}

Pdu_EventSql *Pdu_EventSql::bulid()
{
    static Pdu_EventSql* sington = nullptr;
    if(!sington) sington = new Pdu_EventSql();
    return sington;
}


void Pdu_EventSql::append(uint pdu_id, const QString &type, const QString &content)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->content = content;
    mLstIts.append(it);
}


void Pdu_EventSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, "1","2");
    }insert();
}

