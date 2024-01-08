/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */

#include "httpserverobj.h"


using namespace Qt::StringLiterals;

static inline QString host(const QHttpServerRequest &request)
{
    return QString::fromLatin1(request.value("Host"));
}


HttpServerObj::HttpServerObj(QObject *parent) : QThread{parent}
{
    // mHttpServer.route("/", []() {
    //     return "Hello world";
    // });

    // mHttpServer.route("/query", [] (const QHttpServerRequest &request) {
    //     return host(request) + u"/query/"_s;
    // });

    // mHttpServer.route("/query/", [] (QString id, const QHttpServerRequest &request) {
    //     qDebug() << request.query().queryItems();
    //     return u"%1/query/%2"_s.arg(host(request)).arg(id);
    // });


    // http_listen(mHttpServer, 43796);

}

QString HttpServerObj::queryItem(const QHttpServerRequest &request, const QString &key)
{
    QString res; if(request.query().hasQueryItem(key)) {
        res = request.query().queryItemValue(key);
    }
    return res;
}

void HttpServerObj::init_demo(QHttpServer &httpServer)
{
    httpServer.route("/", []() {
        return "Hello world";
    });

    httpServer.route("/query", [] (const QHttpServerRequest &request) {
        return host(request) + u"/query/"_s;
    });

    httpServer.route("/query/", [] (QString id, const QHttpServerRequest &request) {
        qDebug() << request.query().queryItems();
        return u"%1/query/%2"_s.arg(host(request)).arg(id);
    });

    httpServer.route("/query/<arg>/log", [] (qint32 id, const QHttpServerRequest &request) {
        return u"%1/query/%2/log"_s.arg(host(request)).arg(id);
    });

    httpServer.route("/query/<arg>/log/", [] (qint32 id, float threshold,
                                             const QHttpServerRequest &request) {
        return u"%1/query/%2/log/%3"_s.arg(host(request)).arg(id).arg(threshold);
    });

    httpServer.route("/user/", [] (const qint32 id) {
        return u"User "_s + QString::number(id);
    });

    httpServer.route("/user/<arg>/detail", [] (const qint32 id) {
        return u"User %1 detail"_s.arg(id);
    });

    httpServer.route("/user/<arg>/detail/", [] (const qint32 id, const qint32 year) {
        return u"User %1 detail year - %2"_s.arg(id).arg(year);
    });

    httpServer.route("/json/", [] {
        return QJsonObject{
            {
                {"key1", "1"},
                {"key2", "2"},
                {"key3", "3"}
            }
        };
    });

    httpServer.route("/assets/<arg>", [] (const QUrl &url) {
        return QHttpServerResponse::fromFile(u":/assets/"_s + url.path());
    });

    httpServer.route("/remote_address", [](const QHttpServerRequest &request) {
        return request.remoteAddress().toString();
    });

    // Basic authentication example (RFC 7617)
    httpServer.route("/auth", [](const QHttpServerRequest &request) {
        auto auth = request.value("authorization").simplified();

        if (auth.size() > 6 && auth.first(6).toLower() == "basic ") {
            auto token = auth.sliced(6);
            auto userPass = QByteArray::fromBase64(token);

            if (auto colon = userPass.indexOf(':'); colon > 0) {
                auto userId = userPass.first(colon);
                auto password = userPass.sliced(colon + 1);

                if (userId == "Aladdin" && password == "open sesame")
                    return QHttpServerResponse("text/plain", "Success\n");
            }
        }
        QHttpServerResponse response("text/plain", "Authentication required\n",
                                     QHttpServerResponse::StatusCode::Unauthorized);
        response.setHeader("WWW-Authenticate", R"(Basic realm="Simple example", charset="UTF-8")");
        return response;
    });

    //! [Using afterRequest()]
    httpServer.afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Server", "Qt HTTP Server");
        return std::move(resp);
    });
    //! [Using afterRequest()]
}

bool HttpServerObj::http_listen(quint16 port)
{
    const auto ret = mHttpServer.listen(QHostAddress::Any, port);
    if (!ret) {
        qWarning() << QCoreApplication::translate("QHttpServer", "Server failed to listen on a port.");
        return false;
    }

    return init_ssl(mHttpServer, ret);
}

//! [HTTPS Configuration ]
bool HttpServerObj::init_ssl(QHttpServer &httpServer, quint16 port)
{

#if QT_CONFIG(ssl)
    QString dir = ":/commons/http/assets/";
    const auto sslCertificateChain = QSslCertificate::fromPath(dir + "certificate.crt");
    if (sslCertificateChain.empty()) {
        qWarning() << QCoreApplication::translate("QHttpServer ", "Couldn't retrieve SSL certificate from file.");
        return false;
    }

    QFile privateKeyFile(dir + "private.key");
    if (!privateKeyFile.open(QIODevice::ReadOnly)) {
        qWarning() << QCoreApplication::translate("QHttpServer", "Couldn't open file for reading: %1")
                          .arg(privateKeyFile.errorString());
        return false;
    }

    httpServer.sslSetup(sslCertificateChain.front(), QSslKey(&privateKeyFile, QSsl::Rsa));
    privateKeyFile.close();

    const auto sslPort = httpServer.listen(QHostAddress::Any, port+1);
    if (!sslPort) {
        qWarning() << QCoreApplication::translate("QHttpServer", "Server failed to listen on a port.");
        return false;
    }

    //! [HTTPS Configuration ]
    qInfo().noquote()
        << QCoreApplication::translate("QHttpServer",
                                       "Running on http://127.0.0.1:%1/ and "
                                       "https://127.0.0.1:%2/ (Press CTRL+C to quit)")
               .arg(port).arg(sslPort);
#else
    qInfo().noquote()
        << QCoreApplication::translate("QHttpServer",
                                       "Running on http://127.0.0.1:%1/"
                                       "(Press CTRL+C to quit)").arg(port);
#endif

    return true;
}
