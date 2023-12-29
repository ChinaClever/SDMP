/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduhdasql.h"

PduHdaSql::PduHdaSql()
{
    // test();
}


PduHdaSql *PduHdaSql::bulid()
{
    static PduHdaSql* sington = nullptr;
    if(!sington) sington = new PduHdaSql();
    return sington;
}

void PduHdaSql::append(uint pdu_id, uchar type, uchar topic, uchar indexes, double value)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->topic = topic;
    it->indexes = indexes;
    it->value = value;
    mLstIts.append(it);
}

void PduHdaSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, i, i,i,i);
    }
    insert();
    cout << count();
}
