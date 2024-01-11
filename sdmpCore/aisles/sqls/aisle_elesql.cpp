/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_elesql.h"

Aisle_EleSql::Aisle_EleSql()
{
    mIndexSql = Aisle_IndexSql::build();
}


Aisle_EleSql *Aisle_EleSql::build()
{
    static Aisle_EleSql* sington = nullptr;
    if(!sington) sington = new Aisle_EleSql();
    return sington;
}

AisleEleModel Aisle_EleSql::aisleEleByCab(uint aisleId)
{
    QList<uint> cabLst = mIndexSql->getCabinetIds(aisleId);
    AisleEleModel model; foreach (const auto cab_id, cabLst) {
        CabEleModel cab = Cab_EleSql::build()->cabEle(cab_id);
        model.a_ele += cab.a_ele; model.b_ele += cab.b_ele;
    } model.tg_ele = model.a_ele + model.b_ele;
    model.aisle_id = aisleId;
    return model;
}

void Aisle_EleSql::appendEle(const AisleEleModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}

AisleEleModel Aisle_EleSql::aisleEle(uint id)
{
    AisleEleModel model;
    if(mIndexSql->pdu_bar(id)) {

    } else model = aisleEleByCab(id);
    return model;
}


QJsonObject Aisle_EleSql::aisleEleJson(uint id)
{
    QJsonObject obj;
    AisleEleModel model = aisleEle(id);
    obj.insert("aisle_id", (int)id);
    obj.insert("tg_ele", model.tg_ele);
    obj.insert("a_ele", model.a_ele);
    obj.insert("b_ele", model.b_ele);
    return obj;
}



void Aisle_EleSql::eleWork()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &id, idLst) {
        appendEle(aisleEle(id));
    }


    if(mLstIts.size()) insert();
}
