/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_hdasql.h"

Room_HdaSql::Room_HdaSql()
{
    mIndexSql = Room_IndexSql::build();
}

Room_HdaSql *Room_HdaSql::build()
{
    static Room_HdaSql* sington = nullptr;
    if(!sington) sington = new Room_HdaSql();
    return sington;
}

RoomHdaModel Room_HdaSql::roomHda(uint roomId)
{
    QList<uint> aisleLst = mIndexSql->getAisleIds(roomId);
    RoomHdaModel model; foreach (const auto aisle_id, aisleLst) {
        AisleHdaModel aisle = Aisle_HdaSql::build()->aisleHda(aisle_id);
        model.a_apparent_power += aisle.a_apparent_power;
        model.b_apparent_power += aisle.b_apparent_power;
        model.a_active_power += aisle.a_active_power;
        model.b_active_power += aisle.b_active_power;
    } model.tg_active_power = model.a_active_power + model.b_active_power;
    model.tg_apparent_power = model.a_apparent_power + model.b_apparent_power;
    model.room_id = roomId;
    return model;
}

void Room_HdaSql::appendHda(const RoomHdaModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}


QJsonObject Room_HdaSql::roomHdaJson(uint id)
{
    QJsonObject obj;
    RoomHdaModel model = roomHda(id);  obj.insert("room_id", (int)id);
    obj.insert("tg_apparent_power", model.tg_apparent_power);
    obj.insert("a_apparent_power", model.a_apparent_power);
    obj.insert("b_apparent_power", model.b_apparent_power);
    obj.insert("tg_active_power", model.tg_active_power);
    obj.insert("a_active_power", model.a_active_power);
    obj.insert("b_active_power", model.b_active_power);
    return obj;
}


void Room_HdaSql::hdaWork()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &id, idLst) {
        appendHda(roomHda(id));
    }



    if(mLstIts.size()) insert();
}
