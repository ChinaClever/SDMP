/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_httpserver.h"

Room_HttpServer::Room_HttpServer(QObject *parent)
    : Cab_HttpServer{parent}
{
    room_httpInit();
}

void Room_HttpServer::room_httpInit()
{
    room_ele();
    room_power();
    room_number();
    room_eleList();
    room_nameList();
    room_powerList();
}

void Room_HttpServer::room_number()
{
    mHttpServer.route("/room/number", [&] {
        Room_IndexSql *index = Room_IndexSql::build();
        int number = index->getIds().size(); QJsonObject obj;
        obj.insert("number", number);
        return obj;
    });
}

void Room_HttpServer::room_nameList()
{
    mHttpServer.route("/room/name/list", [&] {
        QJsonArray jsonArray;
        Room_IndexSql *index = Room_IndexSql::build();
        QStringList stringList = index->getNames();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Room_HttpServer::room_powerList()
{
    mHttpServer.route("/room/power/list", [&] {
        Room_IndexSql *index = Room_IndexSql::build();
        QJsonObject obj; QList<uint> lst = index->getIds();
        foreach (const auto& it, lst) {
            QString name = index->getNameById(it);
            QJsonObject json = Room_HdaSql::build()->roomHdaJson(it);
            obj.insert(name, json);
        } return obj;
    });
}

void Room_HttpServer::room_power()
{
    mHttpServer.route("/room/power", [&] (const QHttpServerRequest &request){
        QString name = queryItem(request, "name");
        if(name.size()) {
            Room_IndexSql *index = Room_IndexSql::build();
            uint id = index->getIdByName(name);
            return Room_HdaSql::build()->roomHdaJson(id);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}


void Room_HttpServer::room_ele()
{
    mHttpServer.route("/room/ele", [&] (const QHttpServerRequest &request){
        QString name = queryItem(request, "name");
        if(name.size()) {
            Room_IndexSql *index = Room_IndexSql::build();
            uint id = index->getIdByName(name);
            return Room_EleSql::build()->roomEleJson(id);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Room_HttpServer::room_eleList()
{
    mHttpServer.route("/room/ele/list", [&] {
        Room_IndexSql *index = Room_IndexSql::build();
        QJsonObject obj; QList<uint> lst = index->getIds();
        foreach (const auto& it, lst) {
            QString name = index->getNameById(it);
            QJsonObject json = Room_EleSql::build()->roomEleJson(it);
            obj.insert(name, json);
        } return obj;
    });
}
