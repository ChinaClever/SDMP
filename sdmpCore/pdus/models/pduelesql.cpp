/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduelesql.h"

PduEleSql::PduEleSql()
{
    // test();
}


PduEleSql *PduEleSql::bulid()
{
    static PduEleSql* sington = nullptr;
    if(!sington) sington = new PduEleSql();
    return sington;
}

void PduEleSql::append(uint pdu_id, uchar type, uchar indexes, double value)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->indexes = indexes;
    it->value = value;
    mLstIts.append(it);
}

void PduEleSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, i,i,i);
    }insert();
}
