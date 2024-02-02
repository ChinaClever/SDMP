/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_hdasql.h"

Rack_HdaSql::Rack_HdaSql()
{
    mIndexSql = Rack_IndexSql::build();
}

Rack_HdaSql *Rack_HdaSql::build()
{
    static Rack_HdaSql* sington = nullptr;
    if(!sington) sington = new Rack_HdaSql();
    return sington;
}



bool Rack_HdaSql::a_outlet(uint rack_id, RackHdaModel &model)
{
    uint port = mIndexSql->a_port(rack_id);
    QJsonObject root = mIndexSql->outletByRack(rack_id);
    bool res = false; if(root.size() && port) {
        QJsonObject json = getObject(root, "a_pdu_outlet");
        if(json.size()) {
            QJsonArray array = getArray(json, "apparent_pow");
            model.a_apparent_power = array.at(port-1).toDouble();
            array = getArray(json, "pow_value"); res = true;
            model.a_active_power = array.at(port-1).toDouble();
        }
    }

    return res;
}


bool Rack_HdaSql::b_outlet(uint rack_id, RackHdaModel &model)
{
    uint port = mIndexSql->b_port(rack_id);
    QJsonObject root = mIndexSql->outletByRack(rack_id);
    bool res = false; if(root.size() && port) {
        QJsonObject json = getObject(root, "b_pdu_outlet");
        if(json.size()) {
            QJsonArray array = getArray(json, "apparent_pow");
            model.b_apparent_power = array.at(port-1).toDouble();
            array = getArray(json, "pow_value"); res = true;
            model.b_active_power = array.at(port-1).toDouble();
        }
    }

    return res;
}


RackHdaModel Rack_HdaSql::rackHda(uint rackId)
{
    RackHdaModel model; model.rack_id = rackId;
    a_outlet(rackId, model);  b_outlet(rackId, model);
    model.tg_active_power = model.a_active_power + model.b_active_power;
    model.tg_apparent_power = model.a_apparent_power + model.b_apparent_power;
    return model;
}


void Rack_HdaSql::appendHda(const RackHdaModel &model)
{
    ModelPtr it(addModel());
    *it = model; mLstIts.append(it);
}



QJsonObject Rack_HdaSql::rackHdaJson(uint id)
{
    QJsonObject obj;
    RackHdaModel model = rackHda(id);
    obj.insert("rack_id", (int)id);
    obj.insert("a_active_power", model.a_active_power);
    obj.insert("b_active_power", model.b_active_power);
    obj.insert("tg_active_power", model.tg_active_power);
    obj.insert("a_apparent_power", model.a_apparent_power);
    obj.insert("b_apparent_power", model.b_apparent_power);
    obj.insert("tg_apparent_power", model.tg_apparent_power);
    return obj;
}


int Rack_HdaSql::workDown()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &rack_id, idLst) {
        appendHda(rackHda(rack_id));
    }


    return insert();
}

