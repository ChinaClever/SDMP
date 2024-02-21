/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_httpserver.h"
#include "../sqls/rack_hdasql.h"

Rack_HttpServer::Rack_HttpServer(QObject *parent)
    : Room_HttpServer{parent}
{
    rack_init();
}

void Rack_HttpServer::rack_init()
{
    rack_ele();
    rack_power();
    rack_number();
    rack_nameList();
    rack_powerList();
}

QList<uint> Rack_HttpServer::rack_getIdByQuery(const QHttpServerRequest &request)
{
    uint room_id=0, cab_id=0;
    QString room = queryItem(request, "room");
    if(room.size()) room_id = Room_IndexSql::build()->getIdByName(room);

    QString cab = queryItem(request, "cabinet");
    if(cab.size()) cab_id = Cab_IndexSql::build()->getIdsByName(room_id, cab);
    QList<uint> lst = Rack_IndexSql::build()->getIdsByCab(cab_id);

    QString rack = queryItem(request, "rack");
    if(rack.size()) lst = Rack_IndexSql::build()->getIdsByName(cab_id, rack);

    return lst;
}

void Rack_HttpServer::rack_number()
{
    mHttpServer.route("/rack/number", [&] (const QHttpServerRequest &request){
        int number = rack_getIdByQuery(request).size();
        QJsonObject obj; obj.insert("number", number);
        return obj;
    });
}


void Rack_HttpServer::rack_nameList()
{
    mHttpServer.route("/rack/name/list", [&] (const QHttpServerRequest &request){
        Rack_IndexSql *index = Rack_IndexSql::build();
        QJsonArray jsonArray; QList<uint> lst = rack_getIdByQuery(request);
        foreach (const auto& id, lst) jsonArray.append(index->getNameById(id));
        return jsonArray;
    });
}

void Rack_HttpServer::rack_powerList()
{
    mHttpServer.route("/rack/power/list", [&] (const QHttpServerRequest &request){
        QList<uint> lst = rack_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Rack_IndexSql::build()->getNameById(it);
            QJsonObject json = Rack_HdaSql::build()->rackHdaJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

void Rack_HttpServer::rack_eleList()
{
    mHttpServer.route("/rack/ele/list", [&] (const QHttpServerRequest &request){
        QList<uint> lst = rack_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Rack_IndexSql::build()->getNameById(it);
            QJsonObject json = Rack_EleSql::build()->rackEleJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

void Rack_HttpServer::rack_power()
{
    mHttpServer.route("/rack/power", [&] (const QHttpServerRequest &request){
        QList<uint> lst = rack_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Rack_IndexSql::build()->getNameById(it);
            QJsonObject json = Rack_HdaSql::build()->rackHdaJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

void Rack_HttpServer::rack_ele()
{
    mHttpServer.route("/rack/ele", [&] (const QHttpServerRequest &request){
        QList<uint> lst = rack_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Rack_IndexSql::build()->getNameById(it);
            QJsonObject json = Rack_EleSql::build()->rackEleJson(it);
            obj.insert(name, json);
        } return obj;
    });
}



