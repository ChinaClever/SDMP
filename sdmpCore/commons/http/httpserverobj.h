#ifndef HTTPSERVEROBJ_H
#define HTTPSERVEROBJ_H
#include <QHttpServer>
#include <QHttpServerResponse>

#if QT_CONFIG(ssl)
#  include <QSslCertificate>
#  include <QSslKey>
#endif

#include <QJsonObject>
#include <QtCore>

class HttpServerObj
{
public:
    HttpServerObj();

    void init_demo(QHttpServer &httpServer);
    bool init_ssl(QHttpServer &httpServer, quint16 port);
    bool http_listen(QHttpServer &httpServer, quint16 port);

protected:
    QHttpServer mHttpServer;
};

#endif // HTTPSERVEROBJ_H
