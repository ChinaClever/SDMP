/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_indexsql.h"
#include "pdus/network/pdu_netjsonpack.h"

Rack_IndexSql::Rack_IndexSql()
{

}


Rack_IndexSql *Rack_IndexSql::build()
{
    static Rack_IndexSql* sington = nullptr;
    if(!sington) sington = new Rack_IndexSql();
    return sington;
}


QList<uint> Rack_IndexSql::getIds()
{
    QList<uint> lst;
    foreach (const auto &it, mListModel) {
        if(!it.second.is_delete) lst << it.first;
    }

    return lst;
}

uint Rack_IndexSql::a_port(uint id)
{
    return mListModel.getByKey(id).a_port;
}

uint Rack_IndexSql::b_port(uint id)
{
    return mListModel.getByKey(id).b_port;
}

QJsonObject Rack_IndexSql::outletByRack(uint id)
{
    Pdu_IndexSql *pdu = Pdu_IndexSql::build();
    CabPduModel pduModel; QString aPduKey, bPduKey;    
    RackIndexModel model = mListModel.getByKey(id);
    if(Cab_PduSql::build()->getPdu(model.cabinet_id, pduModel)) {
        aPduKey = pdu->getKey(pduModel.a_pdu_ip, pduModel.a_cas_id);
        bPduKey = pdu->getKey(pduModel.b_pdu_ip, pduModel.b_cas_id);
    }

    QJsonObject a_obj; if(aPduKey.size()) {
        QJsonValue json = Pdu_NetJsonPack::build()->outlet(aPduKey);
        if(json.isObject()) a_obj = json.toObject();
    }

    QJsonObject b_obj; if(bPduKey.size()) {
        QJsonValue json = Pdu_NetJsonPack::build()->outlet(bPduKey);
        if(json.isObject()) b_obj = json.toObject();
    }

    QJsonObject root;
    if(a_obj.size()) root.insert("a_pdu_outlet", a_obj);
    if(b_obj.size()) root.insert("b_pdu_outlet", b_obj);

    return root;
}

