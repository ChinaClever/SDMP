/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_pdusql.h"

Cab_PduSql::Cab_PduSql()
{

}


Cab_PduSql *Cab_PduSql::build()
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

bool Cab_PduSql::getPdu(uint cab_id, CabPduModel &model)
{
    bool ret = mHash.contains(cab_id);
    if(ret) {
        uint id = mHash.value(cab_id);
        model = mListModel.getByKey(id);
    }

    return ret;
}
