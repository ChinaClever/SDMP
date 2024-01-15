/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_barsql.h"

Aisle_BarSql::Aisle_BarSql()
{

}


Aisle_BarSql *Aisle_BarSql::build()
{
    static Aisle_BarSql* sington = nullptr;
    if(!sington) sington = new Aisle_BarSql();
    return sington;
}


void Aisle_BarSql::initFun()
{
    if(syncFun()) mHash.clear(); else return;
    foreach (const auto &it, mListModel) {
        mHash.insert(it.second.aisle_id, it.first);
    }
}

bool Aisle_BarSql::getPdu(uint aisle_id, AisleBarModel &model)
{
    bool ret = mHash.contains(aisle_id);
    if(ret) {
        uint id = mHash.value(aisle_id);
        model = mListModel.getByKey(id);
    }

    return ret;
}
