/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_indexsql.h"

Aisle_IndexSql::Aisle_IndexSql()
{

}


Aisle_IndexSql *Aisle_IndexSql::build()
{
    static Aisle_IndexSql* sington = nullptr;
    if(!sington) sington = new Aisle_IndexSql();
    return sington;
}


QList<uint> Aisle_IndexSql::getIds()
{
    QList<uint> lst;
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete) lst << it.first;
    }

    return lst;
}

QList<uint> Aisle_IndexSql::getCabinetIds(uint id)
{
    return Cab_IndexSql::build()->getIdsByAisle(id);
}

QList<uint> Aisle_IndexSql::getIdsByRoom(uint id)
{
    QList<uint> lst; foreach (const auto &it, mListModel) {
        auto model = it.second; if(!model.is_delete && (model.room_id==id)) lst << it.first;
    }

    return lst;
}

int Aisle_IndexSql::pdu_bar(uint id)
{
    return mListModel.getByKey(id).pdu_bar;
}

QString Aisle_IndexSql::getNameById(uint id)
{
    return mListModel.getByKey(id).name;
}

uint Aisle_IndexSql::getIdByRoomAisle(uint room_id, const QString &name)
{
    QList<uint> lst = getIdsByRoom(room_id);
    foreach (const auto &it, lst) {
        if(name == getNameById(it)) return it;
    }
    return 0;
}
