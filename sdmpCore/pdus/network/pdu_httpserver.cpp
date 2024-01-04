/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_httpserver.h"

Pdu_HttpServer::Pdu_HttpServer(QObject *parent)
{
    mNetJson = Pdu_NetJsonPack::bulid(parent);
    pdu_httpInit(); // http_listen( 43796);
}


void Pdu_HttpServer::pdu_httpInit()
{
    pdu_tg();
    pdu_keys();
    pdu_meta();
    pdu_data();
    pdu_line();
    pdu_loop();
    pdu_env();
    pdu_outlet();
    pdu_group();
    pdu_offline();
    pdu_online();
    pdu_alarm();
}

void Pdu_HttpServer::pdu_meta()
{
    mHttpServer.route("/pdu/meta", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->meta(uuid);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_data()
{
    mHttpServer.route("/pdu/data", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->dev(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_delete()
{
    mHttpServer.route("/pdu/delete", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            bool ret = mNetJson->remove(uuid);
            if(ret) return QJsonObject{ {"msg", "delete ok"} };
            else return QJsonObject{ {"msg", "delete error"} };
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_line()
{
    mHttpServer.route("/pdu/line", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->line(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_loop()
{
    mHttpServer.route("/pdu/loop", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->loop(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}


void Pdu_HttpServer::pdu_outlet()
{
    mHttpServer.route("/pdu/outlet", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->outlet(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_env()
{
    mHttpServer.route("/pdu/env", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->env(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_tg()
{
    mHttpServer.route("/pdu/tg", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->tg(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_group()
{
    mHttpServer.route("/pdu/group", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) {
            return mNetJson->group(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_offline()
{
    mHttpServer.route("/pdu/offline", [&]() {
        QJsonArray jsonArray;
        QStringList stringList = mNetJson->offline_list();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Pdu_HttpServer::pdu_online()
{
    mHttpServer.route("/pdu/online", [&]() {
        QJsonArray jsonArray;
        QStringList stringList = mNetJson->online_list();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Pdu_HttpServer::pdu_alarm()
{
    mHttpServer.route("/pdu/alarm", [&]() {
        return mNetJson->alarm();
    });
}

void Pdu_HttpServer::pdu_keys()
{
    mHttpServer.route("/pdu/keys", [&] {
        QJsonArray jsonArray;
        QStringList stringList = mNetJson->keys();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}
