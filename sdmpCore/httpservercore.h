#ifndef HTTPSERVERCORE_H
#define HTTPSERVERCORE_H
#include "mqttpublishcore.h"

class HttpServerCore : public Rack_HttpServer
{
public:
    HttpServerCore(QObject *parent);
    int http_listen_status();
    int https_listen_status();

private:
    void initHttp();

private:
    bool mHttpStatus = false;
    bool mHttpsStatus = false;
};

#endif // HTTPSERVERCORE_H
