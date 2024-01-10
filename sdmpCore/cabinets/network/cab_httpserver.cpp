/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_httpserver.h"

Cab_HttpServer::Cab_HttpServer(QObject *parent) : Pdu_HttpServer{parent}
{
    cab_init();
}

void Cab_HttpServer::cab_init()
{
    cab_list();
    cab_data();
    cab_datas();
    cab_modified();
}


void Cab_HttpServer::cab_datas()
{
    mHttpServer.route("/cabinet/datas", [&] {
        QJsonArray ids = cab_getIds();
        QJsonObject jsonObj; foreach (const auto &it, ids) {
            uint id = (uint)it.toInt(); jsonObj.insert(QString::number(id), cab_getData(id));
        } return jsonObj;
    });
}

void Cab_HttpServer::cab_modified()
{
    mHttpServer.route("/cabinet/modified", [&] {
        Cab_IndexSql::build()->set();
        return QJsonObject{ {"msg", "ok"} };
    });
}


void Cab_HttpServer::cab_data()
{
    mHttpServer.route("/cabinet/data", [&](const QHttpServerRequest &request) {
        uint id = queryItem(request, "id").toUInt();
        if(id > 0) {
            return cab_getData(id);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

QJsonObject Cab_HttpServer::cab_getData(uint id)
{
    QJsonObject hda = Cab_HdaSql::build()->cabHdaJson(id);
    QJsonObject ele = Cab_EleSql::build()->cabEleJson(id);
    QJsonObject mergedObject(hda);
    for (const QString& key : ele.keys()) {
        mergedObject.insert(key, ele.value(key));
    }
    return mergedObject;
}

QJsonArray Cab_HttpServer::cab_getIds()
{
    QJsonArray jsonArray;
    QList<uint> lst = Cab_IndexSql::build()->getIds();
    foreach (const auto& it, lst) {
        jsonArray.append((int)it);
    } return jsonArray;
}

void Cab_HttpServer::cab_list()
{
    mHttpServer.route("/cabinet/list", [&] {
        return cab_getIds();
    });
}
