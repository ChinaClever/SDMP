/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_alarmsql.h"

Pdu_AlarmSql::Pdu_AlarmSql()
{
    // test();
}


Pdu_AlarmSql *Pdu_AlarmSql::bulid()
{
    static Pdu_AlarmSql* sington = nullptr;
    if(!sington) sington = new Pdu_AlarmSql();
    return sington;
}


void Pdu_AlarmSql::append(uint pdu_id, const QString &status, const QString &content)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->status = status;
    it->content = content;
    mLstIts.append(it);
}


void Pdu_AlarmSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, "1","2");
    }insert();
}
