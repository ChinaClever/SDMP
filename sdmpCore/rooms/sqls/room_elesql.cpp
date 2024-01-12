/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_elesql.h"

Room_EleSql::Room_EleSql()
{
    mIndexSql = Room_IndexSql::build();
}


Room_EleSql *Room_EleSql::build()
{
    static Room_EleSql* sington = nullptr;
    if(!sington) sington = new Room_EleSql();
    return sington;
}


RoomEleModel Room_EleSql::roomEle(uint roomId)
{
    QList<uint> aisleLst = mIndexSql->getAisleIds(roomId);
    RoomEleModel model; foreach (const auto aisle_id, aisleLst) {
        AisleEleModel aisle = Aisle_EleSql::build()->aisleEle(aisle_id);
        model.a_ele += aisle.a_ele; model.b_ele += aisle.b_ele;
    } model.tg_ele = model.a_ele + model.b_ele;
    model.room_id = roomId;
    return model;
}

void Room_EleSql::appendEle(const RoomEleModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}

QJsonObject Room_EleSql::roomEleJson(uint id)
{
    QJsonObject obj;
    RoomEleModel model = roomEle(id);
    obj.insert("room_id", (int)id);
    obj.insert("tg_ele", model.tg_ele);
    obj.insert("a_ele", model.a_ele);
    obj.insert("b_ele", model.b_ele);
    return obj;
}

void Room_EleSql::eleWork()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &id, idLst) {
        appendEle(roomEle(id));
    }


    if(mLstIts.size()) insert();
}
