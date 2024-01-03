/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_elesql.h"

Pdu_EleSql::Pdu_EleSql()
{
    // test();
}


Pdu_EleSql *Pdu_EleSql::bulid()
{
    static Pdu_EleSql* sington = nullptr;
    if(!sington) sington = new Pdu_EleSql();
    return sington;
}

void Pdu_EleSql::append(uint pdu_id, uchar type, uchar indexes, double value)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->indexes = indexes;
    it->value = value;
    mLstIts.append(it);
}

void Pdu_EleSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, i,i,i);
    }insert();
}
