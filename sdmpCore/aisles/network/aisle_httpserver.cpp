/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_httpserver.h"
#include "rooms/sqls/room_indexsql.h"


Aisle_HttpServer::Aisle_HttpServer(QObject *parent)
    : Cab_HttpServer{parent}
{
    aisle_httpInit();
}

void Aisle_HttpServer::aisle_httpInit()
{
    aisle_ele();
    aisle_power();
    aisle_number();
    aisle_nameList();
    aisle_powerList();
    aisle_eleList();
}


void Aisle_HttpServer::aisle_nameList()
{
    mHttpServer.route("/aisle/name/list", [&] (const QHttpServerRequest &request){
        QJsonArray jsonArray; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        if(room.size() && room_id) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            QList<uint> lst = index->getIdsByRoom(room_id);
            foreach (const auto& id, lst) jsonArray.append(index->getNameById(id));
        } else  jsonArray.append("parameter error");
        return jsonArray;
    });
}

void Aisle_HttpServer::aisle_number()
{
    mHttpServer.route("/aisle/number", [&] (const QHttpServerRequest &request){
        QJsonObject obj; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        if(room.size() && room_id) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            int number = index->getIdsByRoom(room_id).size();
            obj.insert("number", number);
        } else  {
            obj.insert("msg","parameter error");
        } return obj;
    });
}


void Aisle_HttpServer::aisle_powerList()
{
    mHttpServer.route("/aisle/power/list", [&] (const QHttpServerRequest &request){
        QJsonObject obj; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        if(room.size() && room_id) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            QList<uint> lst = index->getIdsByRoom(room_id);
            foreach (const auto& it, lst) {
                QString name = index->getNameById(it);
                QJsonObject json = Aisle_HdaSql::build()->aisleHdaJson(it);
                obj.insert(name, json);
            } return obj;
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}


void Aisle_HttpServer::aisle_power()
{
    mHttpServer.route("/aisle/power", [&] (const QHttpServerRequest &request){
        QJsonObject obj; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        QString aisle = queryItem(request, "aisle");
        if(room.size() && room_id && aisle.size()) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            uint id = index->getIdByRoomAisle(room_id, aisle);
            QString name = index->getNameById(id);
            QJsonObject json = Aisle_HdaSql::build()->aisleHdaJson(id);
            obj.insert(name, json); return obj;
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}


void Aisle_HttpServer::aisle_ele()
{
    mHttpServer.route("/aisle/ele", [&] (const QHttpServerRequest &request){
        QJsonObject obj; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        QString aisle = queryItem(request, "aisle");
        if(room.size() && room_id && aisle.size()) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            uint id = index->getIdByRoomAisle(room_id, aisle);
            QString name = index->getNameById(id);
            QJsonObject json = Aisle_EleSql::build()->aisleEleJson(id);
            obj.insert(name, json); return obj;
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}


void Aisle_HttpServer::aisle_eleList()
{
    mHttpServer.route("/aisle/ele/list", [&] (const QHttpServerRequest &request){
        QJsonObject obj; QString room = queryItem(request, "room");
        uint room_id = Room_IndexSql::build()->getIdByName(room);
        if(room.size() && room_id) {
            Aisle_IndexSql *index = Aisle_IndexSql::build();
            QList<uint> lst = index->getIdsByRoom(room_id);
            foreach (const auto& it, lst) {
                QString name = index->getNameById(it);
                QJsonObject json = Aisle_EleSql::build()->aisleEleJson(it);
                obj.insert(name, json);
            } return obj;
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}
