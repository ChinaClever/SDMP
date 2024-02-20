/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "httpservercore.h"

HttpServerCore::HttpServerCore(QObject *parent)
    : Room_HttpServer{parent}
{
    initHttp();
}


void HttpServerCore::initHttp()
{
    sCfgRestItem *it = &CfgCom::build(this)->mCfgRest;
    if(it->http.en) {
        QHostAddress address(it->http.url);
        switch(it->http.acl) {
        case 1: address = QHostAddress::Any; break;
        case 0: address = QHostAddress::LocalHost; break;
        } mHttpStatus = this->http_listen(it->http.port, address);
    }

    if(it->https.en) {
        QHostAddress address(it->https.url);
        switch(it->https.acl) {
        case 1: address = QHostAddress::Any; break;
        case 0: address = QHostAddress::LocalHost; break;
        } mHttpsStatus = this->https_listen(it->https.port, address);
    }
}

int HttpServerCore::http_listen_status()
{
    sCfgRestUnit *it = &CfgCom::build(this)->mCfgRest.http;
    int ret = 0; if(it->en) {
        if(mHttpStatus) ret = 1; else ret = 2;
    }
    return ret;
}

int HttpServerCore::https_listen_status()
{
    sCfgRestUnit *it = &CfgCom::build(this)->mCfgRest.https;
    int ret = 0; if(it->en) {
        if(mHttpsStatus) ret = 1; else ret = 2;
    }
    return ret;
}
