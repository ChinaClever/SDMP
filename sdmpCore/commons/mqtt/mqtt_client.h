#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "qmqtt.h"
#include "cfgcom.h"

class Mqtt_Client : public QObject
{
    Q_OBJECT
    explicit Mqtt_Client(QObject *parent = nullptr);
public:
    static Mqtt_Client *bulid(QObject *parent = nullptr);
    void startMqtt();
    ~Mqtt_Client();

signals:
    void publish(const QString &topic, const QByteArray &payload);

public slots:
    void onConnected();
    void onPublish(const QString &topic, const QByteArray &payload);
    void onDisconnected();//{cfg.isConnected = false;}
    //void onReceived(const QMQTT::Message& message);
    void onError(const QMQTT::ClientError error) {qDebug() << Q_FUNC_INFO << error;}

private:
    bool createMqtt();
    void connectToHost();
    QSslConfiguration sslConfiguration();

private:
    quint16 m_number=0;
    sCfgMqttItem *mCfg;
    QMQTT::Client *m_client=nullptr;
};

#endif // MQTT_CLIENT_H
