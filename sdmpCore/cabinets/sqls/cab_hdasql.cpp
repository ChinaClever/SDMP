/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_hdasql.h"

Cab_HdaSql::Cab_HdaSql()
{
    mPduSql = Cab_PduSql::bulid();
    mIndexSql = Cab_IndexSql::bulid();
}

Cab_HdaSql *Cab_HdaSql::bulid()
{
    static Cab_HdaSql* sington = nullptr;
    if(!sington) sington = new Cab_HdaSql();
    return sington;
}


void Cab_HdaSql::pduHda(uint pdu_id, double &apparent_power, double &active_power)
{
    QString uid = Pdu_IndexSql::bulid()->getKey(pdu_id);
    QJsonValue jsonValue = Pdu_NetJsonPack::bulid()->tg(uid);
    if(jsonValue.isObject()) {
        active_power = getData(jsonValue.toObject(), "pow");
        apparent_power = getData(jsonValue.toObject(), "apparent_pow");
    }
}


void Cab_HdaSql::cabPduHda(uint cab_id)
{
    uint a_pdu=0, b_pdu=0;
    if(mPduSql->getPdu(cab_id, a_pdu, b_pdu)) {
        ModelPtr it(addModel()); it->cabinet_id = cab_id;
        if(a_pdu) pduHda(a_pdu, it->a_apparent_power, it->a_active_power);
        if(b_pdu) pduHda(b_pdu, it->b_apparent_power, it->b_active_power);
        it->tg_apparent_power = it->a_apparent_power + it->b_apparent_power;
        it->tg_active_power = it->a_active_power + it->b_active_power;
        mLstIts.append(it);
    }
}



QJsonObject Cab_HdaSql::cabJsonPduHda(uint cab_id)
{
    uint a_pdu=0, b_pdu=0; QJsonObject obj;
    if(mPduSql->getPdu(cab_id, a_pdu, b_pdu)) {
        double a_apparent_power=0, a_active_power=0;
        if(a_pdu) pduHda(a_pdu, a_apparent_power, a_active_power);

        double b_apparent_power=0, b_active_power=0;
        if(b_pdu) pduHda(b_pdu, b_apparent_power, b_active_power);

        double tg_apparent_power = a_apparent_power + b_apparent_power;
        double tg_active_power = a_active_power + b_active_power;
        obj.insert("tg_apparent_power", tg_apparent_power);
        obj.insert("tg_active_power", tg_active_power);

        obj.insert("a_apparent_power", a_apparent_power);
        obj.insert("b_apparent_power", b_apparent_power);
        obj.insert("a_active_power", a_active_power);
        obj.insert("b_active_power", b_active_power);
        obj.insert("cabinet_id", (int)cab_id);
    }

    return obj;
}


QJsonObject Cab_HdaSql::cabEle(uint cab_id)
{
    int ret = mIndexSql->is_pdu_box(cab_id);
    if(ret) {

    } else  return cabJsonPduHda(cab_id);
}

void Cab_HdaSql::workDown()
{
    QList<uint> pduLst, boxLst;
    mIndexSql->getIds(pduLst, boxLst);
    foreach (const auto &cab_id, pduLst) cabPduHda(cab_id);


}




