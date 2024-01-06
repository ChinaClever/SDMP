/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_pdusql.h"

Cab_PduSql::Cab_PduSql()
{

}


Cab_PduSql *Cab_PduSql::bulid()
{
    static Cab_PduSql* sington = nullptr;
    if(!sington) sington = new Cab_PduSql();
    return sington;
}

void Cab_PduSql::initFun()
{
    fetch_all(); mHash.clear();
    foreach (const auto &it, mListModel) {
        mHash.insert(it.second.cabinet_id, it.first);
    }
}

bool Cab_PduSql::getPdu(uint cab_id, uint &a_pdu, uint &b_pdu)
{
    bool ret = mHash.contains(cab_id);
    if(ret) {
        uint id = mHash.value(cab_id);
        CabPduModel model = mListModel.getByKey(id);
        a_pdu = model.a_pdu_id; b_pdu = model.b_pdu_id;
    }

    return ret;
}
