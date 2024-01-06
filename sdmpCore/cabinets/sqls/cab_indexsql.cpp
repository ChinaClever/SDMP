/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_indexsql.h"

Cab_IndexSql::Cab_IndexSql()
{

}

Cab_IndexSql *Cab_IndexSql::bulid()
{
    static Cab_IndexSql* sington = nullptr;
    if(!sington) sington = new Cab_IndexSql();
    return sington;
}

void Cab_IndexSql::syncFun()
{
    if(isModified) {
        fetch_all(); isModified = false;
        Cab_PduSql::bulid()->initFun();
    }
}

int Cab_IndexSql::getIds(QList<uint> &pdu, QList<uint> &box)
{
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete){
            if(it.second.pdu_box) box << it.first;
            else pdu << it.first;
        }
    }

    return mListModel.size();
}

uchar Cab_IndexSql::is_pdu_box(uint id)
{
    return mListModel.getByKey(id).pdu_box;
}
