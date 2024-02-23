/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mqtt_client.h"
#include <QSslKey>
#include <QSslCertificate>
#include <QSslConfiguration>

Mqtt_Client::Mqtt_Client(QObject *parent)
    : QObject{parent}
{
    mCfg = &CfgCom::build()->mCfgMqtt; startMqtt();
    connect(this, &Mqtt_Client::publish, this, &Mqtt_Client::onPublish);
}

Mqtt_Client::~Mqtt_Client()
{
    if(m_client) m_client->disconnectFromHost();
}

Mqtt_Client *Mqtt_Client::bulid(QObject *parent)
{
    static Mqtt_Client* sington = nullptr;
    if(sington == nullptr) {
        sington = new Mqtt_Client(parent);
    }
    return sington;
}


QSslConfiguration Mqtt_Client::sslConfiguration()
{
    QSslConfiguration ssl;
    QString dir = ":/commons/mqtt/certs/";
    QFile certFile(dir +"cert.pem");
    QFile keyFile(dir +"key.pem");

    bool ret = keyFile.open(QIODevice::ReadOnly);
    if(ret) ret = certFile.open(QIODevice::ReadOnly);
    if(ret) {
        QList< QSslCertificate > caCertificates;
        QSslCertificate sslCertificate( certFile.readAll(), QSsl::Pem );
        QSslKey sslKey( keyFile.readAll(), QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey );
        ssl.setPeerVerifyMode(QSslSocket::VerifyNone);
        ssl.setPeerVerifyDepth( 1 );
        ssl.setLocalCertificate( sslCertificate );
        ssl.setPrivateKey( sslKey );
        ssl.setProtocol(QSsl::AnyProtocol);  //TlsV1_1OrLater
        ssl.setCaCertificates( caCertificates );
    }

    return ssl;
}

bool Mqtt_Client::createMqtt()
{
    bool ret = true;
    if(1 == mCfg->type) {
        QHostAddress host(mCfg->url);
        m_client = new QMQTT::Client(host, mCfg->port, this);
    } else if(2 == mCfg->type) {
        QSslConfiguration ssl = sslConfiguration();
        m_client = new QMQTT::Client(mCfg->url, mCfg->port, ssl, false, this);
    } else if(3 == mCfg->type) {
        QString cmd = "ws://%1:%2%3";
        QString url = cmd.arg(mCfg->url).arg(mCfg->port).arg(mCfg->path);
        m_client = new QMQTT::Client(url, "", QWebSocketProtocol::VersionLatest, false, this);
    } else if(4 == mCfg->type) {
        QString cmd = "wss://%1:%2%3";
        QString url = cmd.arg(mCfg->url).arg(mCfg->port).arg(mCfg->path);
        QSslConfiguration ssl = sslConfiguration();
        m_client = new QMQTT::Client(url, "", QWebSocketProtocol::VersionLatest, ssl, false, this);
    } else {
        ret = false;
    }

    if(ret) {
        connect(m_client, &QMQTT::Client::error, this, &Mqtt_Client::onError);
        //connect(m_client, &QMQTT::Client::received, this, &Mqtt_Client::onReceived);
        connect(m_client, &QMQTT::Client::connected, this, &Mqtt_Client::onConnected);
        connect(m_client, &QMQTT::Client::disconnected, this, &Mqtt_Client::onDisconnected);
    }
    return ret;
}

void Mqtt_Client::connectToHost()
{
    bool ret = createMqtt();
    if(ret) {
        m_client->setKeepAlive(mCfg->keepAlive);
        m_client->setClientId(mCfg->clientId);
        m_client->setAutoReconnect(true);
        m_client->setCleanSession(true);
        m_client->setUsername(mCfg->usr);
        m_client->setPassword(mCfg->pwd);
        m_client->connectToHost();
    } else if(m_client) m_client->setAutoReconnect(ret);
}

void Mqtt_Client::startMqtt()
{
    if(m_client) {
        mCfg->isConnected = false;
        m_client->disconnectFromHost();
        delete m_client; m_client=nullptr;
    }

    if(mCfg->type) connectToHost();
}

void Mqtt_Client::onConnected()
{
    mCfg->isConnected = true;
    //QString topic = "pduSetting/#";// + mCfg->clientId;
    //m_client->subscribe(topic, mCfg->qos);
    qDebug() << "mqtt connected" << mCfg->url << mCfg->isConnected;
}

void Mqtt_Client::onDisconnected()
{
    mCfg->isConnected = false;
    qDebug() << "mqtt disconnected" << mCfg->isConnected;
}

void Mqtt_Client::onPublish(const QString &topic, const QByteArray &payload)
{
    if(mCfg->isConnected /*&& mCfg->clientId.size()*/) {
        QMQTT::Message message(m_number++, topic, payload, mCfg->qos);
        m_client->publish(message); //cout << topic;
    }
}



