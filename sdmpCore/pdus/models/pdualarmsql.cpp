/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdualarmsql.h"

PduAlarmSql::PduAlarmSql()
{
    // test();
}


PduAlarmSql *PduAlarmSql::bulid()
{
    static PduAlarmSql* sington = nullptr;
    if(!sington) sington = new PduAlarmSql();
    return sington;
}


void PduAlarmSql::append(uint pdu_id, const QString &status, const QString &content)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->status = status;
    it->content = content;
    mLstIts.append(it);
}


void PduAlarmSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, "1","2");
    }insert();
}
