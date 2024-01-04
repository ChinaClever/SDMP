#ifndef HTTPSERVEROBJ_H
#define HTTPSERVEROBJ_H
#include <QHttpServer>
#include <QHttpServerResponse>
#if QT_CONFIG(ssl)
#  include <QSslCertificate>
#  include <QSslKey>
#endif

// #include "httpclient.h"
#include <QJsonObject>
#include <QtCore>

class HttpServerObj
{
public:
    HttpServerObj();

    bool http_listen(quint16 port);
    QString queryItem(const QHttpServerRequest &request, const QString &key);

private:
    void init_demo(QHttpServer &httpServer);
    bool init_ssl(QHttpServer &httpServer, quint16 port);

protected:
    QHttpServer mHttpServer;
};

#endif // HTTPSERVEROBJ_H
