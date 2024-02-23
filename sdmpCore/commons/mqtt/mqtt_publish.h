#ifndef MQTT_PUBLISH_H
#define MQTT_PUBLISH_H

#include "mqtt_client.h"

class Mqtt_Publish : public QThread
{
    explicit Mqtt_Publish(QObject *parent = nullptr);
public:
    static Mqtt_Publish *bulid(QObject *parent = nullptr);
    void append(const QString &topic, const QByteArray &payload);
    void append(const QString &topic, const QJsonObject &payload);
    bool isBusy() {return mTopics.size() > 1000;}
    ~Mqtt_Publish();

protected:
    void run();
    void workDown();

private:
    QStringList mTopics;
    QByteArrayList mPayloads;
    sCfgMqttItem *mCfg;
    bool isRun = true;
};

#endif // MQTT_PUBLISH_H
