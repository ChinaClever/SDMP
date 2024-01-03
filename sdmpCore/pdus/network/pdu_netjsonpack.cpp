/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_netjsonpack.h"

Pdu_NetJsonPack::Pdu_NetJsonPack(QObject *parent) : QThread(parent)
{
    mUdp = new Pdu_UdpReceiver(parent);
    mTimer = new QTimer(this); mTimer->start(3500); this->start();
    connect(mTimer, &QTimer::timeout, this, &Pdu_NetJsonPack::onTimeout);
}

Pdu_NetJsonPack::~Pdu_NetJsonPack()
{
    isRun = false;
    wait();
}

Pdu_NetJsonPack *Pdu_NetJsonPack::bulid(QObject *parent)
{
    static Pdu_NetJsonPack* sington = nullptr;
    if(!sington) sington = new Pdu_NetJsonPack(parent);
    return sington;
}


void Pdu_NetJsonPack::online_offline_update()
{
    QString str = "uptime";
    foreach (const auto &it, mHash.values()) {
        if(it->contains(str)) {
            QString key = it->value("uuid").toString();
            QDateTime overtime = QDateTime::currentDateTime().addSecs(-12);
            QDateTime uptime = QDateTime::fromString(it->value(str).toString(), "yyyy-MM-dd hh:mm:ss");
            if(uptime >= overtime) {
                if(mOnlineHash.contains(key) && (mOnlineHash[key] != true)) {
                    emit online_offline_sig(key, true);
                } mOnlineHash[key] = true;
            } else {
                if(mOnlineHash.contains(key) && mOnlineHash[key] != false) {
                    emit online_offline_sig(key, false);
                    it->insert("status", 5); it->insert("pdu_alarm", "Offline");
                } mOnlineHash[key] = false;
            }
        }
    }
}

QStringList Pdu_NetJsonPack::online_list()
{
    QStringList lst;
    foreach (const auto &key, mOnlineHash.keys()) {
        if(!mOnlineHash.value(key)) lst << key;
    }
    return lst;
}

QStringList Pdu_NetJsonPack::offline_list()
{
    QStringList lst;
    foreach (const auto &key, mOnlineHash.keys()) {
        if(mOnlineHash.value(key)) lst << key;
    }
    return lst;
}

void Pdu_NetJsonPack::toJson(QByteArray &datagram, const QString &ip)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            jsonObj.insert("ip", ip); QString uid;
            if(jsonObj.contains("uuid")) {
                uid = jsonObj["uuid"].toString();
            } else if(jsonObj.contains("addr")) {
                int addr = jsonObj["addr"].toInt();
                uid = ip + "_" + QString::number(addr);
            } else {
                qDebug() << "UDP datagram error";
                return ;
            }

            QDateTime datetime = QDateTime::currentDateTime();
            jsonObj.insert("uptime", datetime.toString("yyyy-MM-dd hh:mm:ss"));
            QSharedPointer<QJsonObject> sharedPtr(new QJsonObject(jsonObj));
            mHash.insert(uid, sharedPtr);  //qDebug() << ip;
        } else {
            qDebug() << "JSON document is not an object";
        }
    } else {
        qDebug() << "Failed to parse JSON";
    }
}

bool Pdu_NetJsonPack::workDown()
{
    QSharedPointer<sUdpRcvItem> it; bool ret = mUdp->get(it);
    if(ret) toJson(it->datagram, it->address.toString().remove("::ffff:"));
    return ret;
}

void Pdu_NetJsonPack::run()
{
    bool ret = false;
    while(isRun) {
        ret = workDown();
        if(!ret) QThread::msleep(1);
    }
}


QSharedPointer<QJsonObject> Pdu_NetJsonPack::shredPointer(const QString &key)
{
    return mHash.value(key);
}

QJsonObject Pdu_NetJsonPack::meta(const QString &key)
{
    if(mHash.contains(key)) {
        QSharedPointer<QJsonObject> sptr = shredPointer(key);
        return *sptr;
    }
    return QJsonObject();
}

QJsonValue Pdu_NetJsonPack::getJsonObject(const QString &uuid, const QString &key)
{
    QJsonValue value;
    bool ret = mHash.contains(uuid);
    if(ret) {
        QSharedPointer<QJsonObject> sptr = shredPointer(uuid);
        value = sptr->value(key);
    }
    return value;
}

QJsonObject Pdu_NetJsonPack::alarm()
{
    QJsonObject obj;
    foreach (const auto &it, mHash.values()) {
        int status = it->value("status").toInt();
        if(0 != status) {
            QString key = it->value("uuid").toString();
            QString alarm = it->value("pdu_alarm").toString();
            obj.insert(key, alarm);
        }
    }
    return obj;
}


QJsonValue Pdu_NetJsonPack::dev(const QString &key)
{
    return getJsonObject(key, "pdu_data");
}

QJsonValue Pdu_NetJsonPack::line(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("line_item_list");
    return value;
}

QJsonValue Pdu_NetJsonPack::loop(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("loop_item_list");
    return value;
}

QJsonValue Pdu_NetJsonPack::outlet(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("output_item_list");
    return value;
}

QJsonValue Pdu_NetJsonPack::group(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("group_item_list");
    return value;
}

QJsonValue Pdu_NetJsonPack::tg(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("pdu_tg_data");
    return value;
}

QJsonValue Pdu_NetJsonPack::env(const QString &key)
{
    QJsonValue value = dev(key);
    if(value.isObject()) value = value.toObject().value("env_item_list");
    return value;
}


QString Pdu_NetJsonPack::getKey(const QString &ip, uchar addr)
{
    foreach (const auto &it, mHash.values()) {
        int src_addr = it->value("addr").toInt();
        QString src_ip = it->value("ip").toString();
        QString uuid = it->value("uuid").toString();
        if((src_ip == ip) && (addr == src_addr)) return uuid;
    }
    return "";
}

void Pdu_NetJsonPack::append(const QString &key, const QString &ip, uchar addr)
{
    QSharedPointer<QJsonObject> jsonObj;
    if(mHash.contains(key)) {
        jsonObj = mHash.value(key);
    } else {
        jsonObj = QSharedPointer<QJsonObject>(new QJsonObject());
        jsonObj->insert("status", 5);
    }

    jsonObj->insert("ip", ip);
    jsonObj->insert("addr", addr);
    QDateTime datetime = QDateTime::currentDateTime();
    jsonObj->insert("uptime", datetime.toString("yyyy-MM-dd hh:mm:ss"));
    mHash.insert(key, jsonObj);
}


QString Pdu_NetJsonPack::toUid(const QString &ip, uchar addr)
{
    QString key = ip + "_" + QString::number(addr);
    return key;
}
