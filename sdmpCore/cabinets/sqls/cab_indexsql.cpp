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

QString Cab_IndexSql::getNameById(uint id)
{
    QString res=0; if(mListModel.contains(id))
        res = mListModel.getByKey(id).name;
    return res;
}

uint Cab_IndexSql::roomId(uint id)
{
    uint res=0; if(mListModel.contains(id))
        res = mListModel.getByKey(id).room_id;
    return res;
}

QList<uint> Cab_IndexSql::getIds()
{
    QList<uint> lst;
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete) lst << it.first;
    }

    return lst;
}

QList<uint> Cab_IndexSql::getIdsByRoom(uint room_id)
{
    QList<uint> lst; foreach (const auto &it, mListModel) {
        auto model = it.second; if(!model.is_delete && (model.room_id==room_id)) lst << it.first;
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

QList<uint> Cab_IndexSql::getIdsByRoomAisle(uint room_id, uint aisle_id)
{
    QList<uint> lst; if(room_id && aisle_id) {
         foreach (const auto &it, mListModel) {
            auto model = it.second; if(!model.is_delete && (model.aisle_id==aisle_id) && (model.room_id==room_id)) lst << it.first;
        }
    } else if(room_id) lst = getIdsByRoom(room_id);
    else if(aisle_id) lst = getIdsByAisle(aisle_id);
    else lst = getIds();

    return lst;
}

QList<uint> Cab_IndexSql::getIdsByName(QList<uint> &id, const QString &name)
{
    QList<uint> lst;
    foreach (const auto &it, id) {
        if(getNameById(it) == name) lst << it;
    }
    return lst;
}

uint Cab_IndexSql::getIdsByName(uint room_id, const QString &cab)
{    
    QList<uint> lst = getIdsByRoom(room_id);
    uint ret = 0; lst = getIdsByName(lst, cab);
    if(lst.size()) ret = lst.first();
    return ret;
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
