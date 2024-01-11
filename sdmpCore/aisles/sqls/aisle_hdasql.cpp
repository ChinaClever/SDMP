/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_hdasql.h"

Aisle_HdaSql::Aisle_HdaSql()
{
    mIndexSql = Aisle_IndexSql::build();
}


Aisle_HdaSql *Aisle_HdaSql::build()
{
    static Aisle_HdaSql* sington = nullptr;
    if(!sington) sington = new Aisle_HdaSql();
    return sington;
}


AisleHdaModel Aisle_HdaSql::aisleHdaByCab(uint aisleId)
{
    QList<uint> cabLst = mIndexSql->getCabinetIds(aisleId);
    AisleHdaModel model; foreach (const auto cab_id, cabLst) {
        CabHdaModel cab = Cab_HdaSql::build()->cabHda(cab_id);
        model.a_apparent_power += cab.a_apparent_power;
        model.b_apparent_power += cab.b_apparent_power;
        model.a_active_power += cab.a_active_power;
        model.b_active_power += cab.b_active_power;
    } model.tg_active_power = model.a_active_power + model.b_active_power;
    model.tg_apparent_power = model.a_apparent_power + model.b_apparent_power;
    model.aisle_id = aisleId;
    return model;
}


void Aisle_HdaSql::appendHda(const AisleHdaModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}


AisleHdaModel Aisle_HdaSql::aisleHda(uint id)
{
    AisleHdaModel model;
    if(mIndexSql->pdu_bar(id)) {

    } else model = aisleHdaByCab(id);
    return model;
}



QJsonObject Aisle_HdaSql::aisleHdaJson(uint id)
{
    QJsonObject obj;
    AisleHdaModel model = aisleHda(id);  obj.insert("aisle_id", (int)id);
    obj.insert("tg_apparent_power", model.tg_apparent_power);
    obj.insert("a_apparent_power", model.a_apparent_power);
    obj.insert("b_apparent_power", model.b_apparent_power);
    obj.insert("tg_active_power", model.tg_active_power);
    obj.insert("a_active_power", model.a_active_power);
    obj.insert("b_active_power", model.b_active_power);
    return obj;
}


void Aisle_HdaSql::hdaWork()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &id, idLst) {
        appendHda(aisleHda(id));
    }



    if(mLstIts.size()) insert();
}

