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

class HttpServerObj : public QThread
{
public:
    explicit HttpServerObj(QObject *parent = nullptr);

    bool http_listen(quint16 port, const QHostAddress &address);
    bool https_listen(quint16 port, const QHostAddress &address);
    QString queryItem(const QHttpServerRequest &request, const QString &key);

private:
    void init_demo(QHttpServer &httpServer);

protected:
    QHttpServer mHttpServer;
};

#endif // HTTPSERVEROBJ_H
