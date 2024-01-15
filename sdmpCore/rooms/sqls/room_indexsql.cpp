/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_indexsql.h"

Room_IndexSql::Room_IndexSql()
{

}


Room_IndexSql *Room_IndexSql::build()
{
    static Room_IndexSql* sington = nullptr;
    if(!sington) sington = new Room_IndexSql();
    return sington;
}


QList<uint> Room_IndexSql::getIds()
{
    QList<uint> lst;
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete) lst << it.first;
    }

    return lst;
}

QList<uint> Room_IndexSql::getAisleIds(uint id)
{
    return Aisle_IndexSql::build()->getIdsByRoom(id);
}
