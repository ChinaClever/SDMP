/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_elesql.h"


Cab_EleSql::Cab_EleSql()
{
    mPduSql = Cab_PduSql::bulid();
    mIndexSql = Cab_IndexSql::bulid();
}

Cab_EleSql *Cab_EleSql::bulid()
{
    static Cab_EleSql* sington = nullptr;
    if(!sington) sington = new Cab_EleSql();
    return sington;
}


bool Cab_EleSql::pduTgEle(uint pdu_id, double &ele)
{
    QString uid = Pdu_IndexSql::bulid()->getKey(pdu_id);
    QJsonValue jsonValue = Pdu_NetJsonPack::bulid()->tg(uid);
    bool ret = jsonValue.isObject();
    if(ret) ele = getData(jsonValue.toObject(), "ele");
    return ret;
}

void Cab_EleSql::cabPduEle(uint cab_id)
{
    uint a_pdu=0, b_pdu=0; bool a_ret=false, b_ret=false;
    if(mPduSql->getPdu(cab_id, a_pdu, b_pdu)) {
        ModelPtr it(addModel()); it->cabinet_id = cab_id;
        if(a_pdu) a_ret = pduTgEle(a_pdu, it->a_ele);
        if(b_pdu) b_ret = pduTgEle(b_pdu, it->b_ele);
        if(a_ret || b_ret) {
            it->tg_ele = it->a_ele + it->b_ele;
            mLstIts.append(it);
        }
    }
}

QJsonObject Cab_EleSql::cabJsonPduEle(uint cab_id)
{
    uint a_pdu=0, b_pdu=0; QJsonObject obj;
    if(mPduSql->getPdu(cab_id, a_pdu, b_pdu)) {
        double a_ele=0;  pduTgEle(a_pdu, a_ele);
        double b_ele=0; pduTgEle(b_pdu, b_ele);
        double tg_ele = a_ele + b_ele;
        obj.insert("cabinet_id", (int)cab_id);
        obj.insert("a_ele", a_ele);
        obj.insert("b_ele", b_ele);
        obj.insert("tg_ele", tg_ele);
    }

    return obj;
}


QJsonObject Cab_EleSql::cabEle(uint cab_id)
{
    int ret = mIndexSql->is_pdu_box(cab_id);
    if(ret) {

    } else  return cabJsonPduEle(cab_id);
}



void Cab_EleSql::workDown()
{
    QList<uint> pduLst, boxLst;
    mIndexSql->getIds(pduLst, boxLst);
    foreach (const auto &cab_id, pduLst) cabPduEle(cab_id);


    if(mLstIts.size()) insert();

}
