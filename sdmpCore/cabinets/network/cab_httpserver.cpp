/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_httpserver.h"
#include "rooms/sqls/room_indexsql.h"
#include "aisles/sqls/aisle_indexsql.h"

Cab_HttpServer::Cab_HttpServer(QObject *parent) : Pdu_HttpServer{parent}
{
    cab_init();
}

void Cab_HttpServer::cab_init()
{
    cab_ele();
    cab_power();
    cab_number();
    cab_nameList();
    cab_powerList();
    cab_eleList();
}

QList<uint> Cab_HttpServer::cab_getIdByQuery(const QHttpServerRequest &request)
{
    uint room_id=0, aisle_id=0;
    QString room = queryItem(request, "room");
    if(room.size()) room_id = Room_IndexSql::build()->getIdByName(room);

    QString aisle = queryItem(request, "aisle");
    if(aisle.size()) aisle_id = Aisle_IndexSql::build()->getIdByRoomAisle(room_id, aisle);
    QList<uint> lst = Cab_IndexSql::build()->getIdsByRoomAisle(room_id, aisle_id);
    QString cab = queryItem(request, "cabinet");
    if(cab.size()) lst = Cab_IndexSql::build()->getIdsByName(lst, cab);
    return lst;
}

void Cab_HttpServer::cab_number()
{
    mHttpServer.route("/cabinet/number", [&] (const QHttpServerRequest &request){
        int number = cab_getIdByQuery(request).size();
        QJsonObject obj; obj.insert("number", number);
        return obj;
    });
}

void Cab_HttpServer::cab_nameList()
{
    mHttpServer.route("/cabinet/name/list", [&] (const QHttpServerRequest &request){
        Cab_IndexSql *index = Cab_IndexSql::build();
        QJsonArray jsonArray; QList<uint> lst = cab_getIdByQuery(request);
        foreach (const auto& id, lst) jsonArray.append(index->getNameById(id));
        return jsonArray;
    });
}

void Cab_HttpServer::cab_powerList()
{
    mHttpServer.route("/cabinet/power/list", [&] (const QHttpServerRequest &request){
        QList<uint> lst = cab_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Cab_IndexSql::build()->getNameById(it);
            QJsonObject json = Cab_HdaSql::build()->cabHdaJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

void Cab_HttpServer::cab_eleList()
{
    mHttpServer.route("/cabinet/ele/list", [&] (const QHttpServerRequest &request){
        QList<uint> lst = cab_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Cab_IndexSql::build()->getNameById(it);
            QJsonObject json = Cab_EleSql::build()->cabEleJson(it);
            obj.insert(name, json);
        } return obj;
    });
}


void Cab_HttpServer::cab_power()
{
    mHttpServer.route("/cabinet/power", [&] (const QHttpServerRequest &request){
        QList<uint> lst = cab_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Cab_IndexSql::build()->getNameById(it);
            QJsonObject json = Cab_HdaSql::build()->cabHdaJson(it);
            obj.insert(name, json);
        } return obj;
    });
}


void Cab_HttpServer::cab_ele()
{
    mHttpServer.route("/cabinet/ele", [&] (const QHttpServerRequest &request){
        QList<uint> lst = cab_getIdByQuery(request);
        QJsonObject obj; foreach (const auto& it, lst) {
            QString name = Cab_IndexSql::build()->getNameById(it);
            QJsonObject json = Cab_EleSql::build()->cabEleJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

