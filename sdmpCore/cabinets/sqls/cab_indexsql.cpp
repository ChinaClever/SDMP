/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_indexsql.h"

Cab_IndexSql::Cab_IndexSql()
{

}

Cab_IndexSql *Cab_IndexSql::build()
{
    static Cab_IndexSql* sington = nullptr;
    if(!sington) sington = new Cab_IndexSql();
    return sington;
}

void Cab_IndexSql::syncFun()
{
    if(isModified) {
        fetch_all(); isModified = false;
        Cab_PduSql::build()->initFun();
    }
}

QList<uint> Cab_IndexSql::getIds()
{
    QList<uint> lst;
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete) lst << it.first;
    }

    return lst;
}

QList<uint> Cab_IndexSql::getIdsByAisle(uint aisle_id)
{
    QList<uint> lst; foreach (const auto &it, mListModel) {
        auto model = it.second; if(!model.is_delete && (model.aisle_id==aisle_id)) lst << it.first;
    }

    return lst;
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

double Cab_IndexSql::pow_capacity(uint id)
{
    return mListModel.getByKey(id).pow_capacity;
}

int Cab_IndexSql::is_disabled(uint id)
{
    return mListModel.getByKey(id).is_disabled;
}
