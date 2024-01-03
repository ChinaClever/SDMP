/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_hdasql.h"

Pdu_HdaSql::Pdu_HdaSql()
{
    // test();
}


Pdu_HdaSql *Pdu_HdaSql::bulid()
{
    static Pdu_HdaSql* sington = nullptr;
    if(!sington) sington = new Pdu_HdaSql();
    return sington;
}

void Pdu_HdaSql::append(uint pdu_id, uchar type, uchar topic, uchar indexes, double value)
{
    ModelPtr it(addModel());
    it->pdu_id = pdu_id;
    it->type = type;
    it->topic = topic;
    it->indexes = indexes;
    it->value = value;
    mLstIts.append(it);
}

void Pdu_HdaSql::test()
{
    for(int i=0; i<5; ++i) {
        append(i, i, i,i,i);
    }
    insert();
    cout << count();
}
