/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mqtt_publish.h"

Mqtt_Publish::Mqtt_Publish(QObject *parent)
    : QThread{parent}
{
    mCfg = &CfgCom::build()->mCfgMqtt;
    start();
}


Mqtt_Publish::~Mqtt_Publish()
{
    wait();
}

Mqtt_Publish *Mqtt_Publish::bulid(QObject *parent)
{
    static Mqtt_Publish* sington = nullptr;
    if(sington == nullptr) {
        sington = new Mqtt_Publish(parent);
    }
    return sington;
}

void Mqtt_Publish::append(const QString &topic, const QByteArray &payload)
{
    if(mCfg->isConnected) {
        mTopics << topic;
        mPayloads << payload;
    }
}

void Mqtt_Publish::append(const QString &topic, const QJsonObject &payload)
{
    QJsonDocument jsonDoc(payload);
    append(topic, jsonDoc.toJson());
}

void Mqtt_Publish::workDown()
{
    QString topic = mTopics.takeFirst();
    QByteArray payload = mPayloads.takeFirst();
    emit Mqtt_Client::bulid()->publish(topic, payload);
}

void Mqtt_Publish::run()
{
    sleep(1);
    uint cnt = 0;
    while(isRun) {
         if(mTopics.size()) {
            if(cnt++%10)workDown();
            else msleep(1);
        } else msleep(1);
    }
}

