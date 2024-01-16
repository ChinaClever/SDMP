/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_elesql.h"

Rack_EleSql::Rack_EleSql()
{
    mIndexSql = Rack_IndexSql::build();
}

Rack_EleSql *Rack_EleSql::build()
{
    static Rack_EleSql* sington = nullptr;
    if(!sington) sington = new Rack_EleSql();
    return sington;
}

double Rack_EleSql::a_outlet(uint rack_id)
{
    uint port = mIndexSql->a_port(rack_id);
    QJsonObject root = mIndexSql->outletByRack(rack_id);
    double res = 0; if(root.size() && port) {
        QJsonObject json = getObject(root, "a_pdu_outlet");
        if(json.size()) {
            QJsonArray array = getArray(json, "ele");
            res = array.at(port-1).toDouble();
        }
    }
    return res;
}


double Rack_EleSql::b_outlet(uint rack_id)
{
    uint port = mIndexSql->b_port(rack_id);
    QJsonObject root = mIndexSql->outletByRack(rack_id);
    double res = 0; if(root.size() && port) {
        QJsonObject json = getObject(root, "b_pdu_outlet");
        if(json.size()) {
            QJsonArray array = getArray(json, "ele");
            res = array.at(port-1).toDouble();
        }
    }
    return res;
}


RackEleModel Rack_EleSql::rackEle(uint rackId)
{
    RackEleModel model;
    model.rack_id = rackId;
    model.a_ele = a_outlet(rackId);
    model.b_ele = b_outlet(rackId);
    model.tg_ele = model.a_ele + model.b_ele;

    return model;
}


void Rack_EleSql::appendEle(const RackEleModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}

QJsonObject Rack_EleSql::rackEleJson(uint id)
{
    QJsonObject obj;
    RackEleModel model = rackEle(id);
    obj.insert("rack_id", (int)id);
    obj.insert("tg_ele", model.tg_ele);
    obj.insert("a_ele", model.a_ele);
    obj.insert("b_ele", model.b_ele);
    return obj;
}


void Rack_EleSql::eleWork()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &rack_id, idLst) {
        appendEle(rackEle(rack_id));
    }


    if(mLstIts.size()) insert();
}
