/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_httpserver.h"

Pdu_HttpServer::Pdu_HttpServer(QObject *parent): HttpServerObj{parent}
{
    pdu_httpInit();
}


void Pdu_HttpServer::pdu_httpInit()
{
    pdu_tg();
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
    pdu_number();
    pdu_dataByIp();
    pdu_keyByIp();
    pdu_keyList();
    pdu_keyToIpList();
}

void Pdu_HttpServer::pdu_initObj()
{
    if(!mNetJson) {
        mNetJson = Pdu_NetJsonPack::build();
    }
}

void Pdu_HttpServer::pdu_number()
{
    mHttpServer.route("/pdu/number", [&] {
        QJsonObject obj; pdu_initObj();
        int number = mNetJson->keys().size();
        int offline = mNetJson->offline_list().size();
        int online = mNetJson->online_list().size();
        int alarm = mNetJson->alarm().size();
        obj.insert("number", number);
        obj.insert("offline", offline);
        obj.insert("online", online);
        obj.insert("alarm", alarm);
        return obj;
    });
}


void Pdu_HttpServer::pdu_meta()
{
    mHttpServer.route("/pdu/meta", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) { pdu_initObj();
            return mNetJson->meta(uuid);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_dataByIp()
{
    mHttpServer.route("/pdu/data/by/ip", [&](const QHttpServerRequest &request) {
        int addr = queryItem(request, "addr").toInt();
        QString ip = queryItem(request, "ip");
        if(addr<0) addr = 0;
        if(ip.size()) { pdu_initObj();
            QString key = mNetJson->getKey(ip, addr);
            return mNetJson->meta(key);
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_data()
{
    mHttpServer.route("/pdu/data", [&](const QHttpServerRequest &request) {
        QString uuid = queryItem(request, "key");
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
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
        if(uuid.size()) { pdu_initObj();
            return mNetJson->group(uuid).toObject();
        } else {
            return QJsonObject{ {"msg", "parameter error"} };
        }
    });
}

void Pdu_HttpServer::pdu_offline()
{
    mHttpServer.route("/pdu/offline/list", [&]() {
        QJsonArray jsonArray; pdu_initObj();
        QStringList stringList = mNetJson->offline_list();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Pdu_HttpServer::pdu_online()
{
    mHttpServer.route("/pdu/online/list", [&]() {
        QJsonArray jsonArray; pdu_initObj();
        QStringList stringList = mNetJson->online_list();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Pdu_HttpServer::pdu_alarm()
{
    mHttpServer.route("/pdu/alarm/list", [&]() {
        pdu_initObj(); return mNetJson->alarm();
    });
}

void Pdu_HttpServer::pdu_keyList()
{
    mHttpServer.route("/pdu/key/list", [&] {
        QJsonArray jsonArray; pdu_initObj();
        QStringList stringList = mNetJson->keys();
        foreach (const QString& str, stringList) {
            jsonArray.append(str);
        } return jsonArray;
    });
}

void Pdu_HttpServer::pdu_keyToIpList()
{
    mHttpServer.route("/pdu/key/to/ip/list", [&] {
        QJsonObject obj; QString ip; uchar addr = 0;
        QStringList stringList = mNetJson->keys();
        foreach (const QString& key, stringList) {
            Pdu_NetJsonPack::build()->getByKey(key, ip, addr);
            QString fmd = "ip=%1 addr=%2";
            obj.insert(key, fmd.arg(ip).arg(addr));
        } return obj;
    });
}



void Pdu_HttpServer::pdu_keyByIp()
{
    mHttpServer.route("/pdu/key/by/ip", [&](const QHttpServerRequest &request) {
        QString ip; uchar addr = 0; QJsonObject obj; pdu_initObj();
        QString key = queryItem(request, "key");
        mNetJson->getByKey(key, ip, addr);
        obj.insert("addr", addr);
        obj.insert("key", key);
        obj.insert("ip", ip);
        return obj;
    });
}
