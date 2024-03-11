/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_netjsonpack.h"

Pdu_NetJsonPack::Pdu_NetJsonPack(QObject *parent) : QThread{parent}
{
    mUdp = Pdu_UdpReceiver::build(this); start();
    // QTimer::singleShot(2450,this,SLOT(onTimeout()));
    // timer = new QTimer(this); timer->start(2500);
    // connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    // QtConcurrent::run([&]{timeoutDone();});
}

Pdu_NetJsonPack::~Pdu_NetJsonPack()
{
    isRun = false;
    wait();
}

Pdu_NetJsonPack *Pdu_NetJsonPack::build(QObject *parent)
{
    static Pdu_NetJsonPack* sington = nullptr;
    if(!sington) sington = new Pdu_NetJsonPack(parent);
    return sington;
}


void Pdu_NetJsonPack::online_offline_update()
{
    QString str = "uptime"; if(!isRun) return;
    foreach (const auto &it, mHash.values()) {
        if(it->contains(str)) {
            QString key = it->value("dev_key").toString();
            QDateTime overtime = QDateTime::currentDateTime().addSecs(-25);
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
        } else cout << "uptime error";
    }
}

void Pdu_NetJsonPack::timeoutDone()
{

}

void Pdu_NetJsonPack::onTimeout()
{
    static QTime t = QTime::currentTime();
    QTime c = QTime::currentTime();
    QTime s = t.addSecs(3);
    if(c > s) {
        online_offline_update();
        t = c; //cout << isRun;
    }
}

QStringList Pdu_NetJsonPack::online_list()
{
    QStringList lst;
    foreach (const auto &key, mOnlineHash.keys()) {
        if(mOnlineHash.value(key)) lst << key;
    }
    return lst;
}

QStringList Pdu_NetJsonPack::offline_list()
{
    QStringList lst;
    foreach (const auto &key, mOnlineHash.keys()) {
        if(!mOnlineHash.value(key)) lst << key;
    }
    return lst;
}

void Pdu_NetJsonPack::toJson(QByteArray &datagram, const QString &ip)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram);
    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();           
            QString dev_key; jsonObj.insert("ip", ip);
            if(jsonObj.contains("uuid"))  {
                dev_key = jsonObj["uuid"].toString();
            } else if(jsonObj.contains("addr")) {
                int addr = jsonObj["addr"].toInt();
                dev_key = ip + "_" + QString::number(addr);
            } else { cout << "UDP datagram error"; return ; }

            jsonObj.insert("dev_key", dev_key);
            QDateTime datetime = QDateTime::currentDateTime();
            jsonObj.insert("uptime", datetime.toString("yyyy-MM-dd hh:mm:ss"));
            QSharedPointer<QJsonObject> sharedPtr(new QJsonObject(jsonObj));
            mHash.insert(dev_key, sharedPtr); //cout << ip << dev_key;
        } else cout << "PDU JSON document is not an object";
    } else cout << "PDU Failed to parse JSON";
}

bool Pdu_NetJsonPack::workDown()
{
    QSharedPointer<sUdpRcvItem> it; bool ret = mUdp->get(it); if(ret) mCnt++;
    if(ret) toJson(it->datagram, it->address.toString().remove("::ffff:"));
    return ret;
}

void Pdu_NetJsonPack::run()
{
    bool ret = false;
    sleep(1); while(isRun) {
        ret = workDown();
        if(!ret) msleep(1);
        onTimeout();
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

QJsonValue Pdu_NetJsonPack::getJsonObject(const QString &dev, const QString &key)
{
    QJsonValue value;
    bool ret = mHash.contains(dev);
    if(ret) {
        QSharedPointer<QJsonObject> sptr = shredPointer(dev);
        value = sptr->value(key);
    }
    return value;
}

QString Pdu_NetJsonPack::alarm(const QString &key)
{
    QString res; auto it = mHash.value(key);
    int status = it->value("status").toInt();
    if(0 != status) {
        QString fmd = "ip=%1 addr=%2 alarm:%3";
        QString key = it->value("dev_key").toString();
        QString alarm = it->value("pdu_alarm").toString();
        QString ip = it->value("ip").toString();
        int addr = it->value("addr").toInt();
        res = fmd.arg(ip).arg(addr).arg(alarm);
        if(5==status) res += "offline";
    }
    return res;
}

QJsonObject Pdu_NetJsonPack::alarms()
{
    QJsonObject obj; QStringList lst = alarm_list();
    foreach (const auto &it, lst) obj.insert(it, alarm(it));
    return obj;
}

QStringList Pdu_NetJsonPack::alarm_list()
{
    QStringList lst;
    foreach (const auto &it, mHash.values()) {
        int status = it->value("status").toInt();
        if(status) lst << it->value("dev_key").toString();
    }
    return lst;
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

bool Pdu_NetJsonPack::is_online(const QString &key)
{
    bool ret = mOnlineHash.contains(key);
    if(ret) {
        ret = mOnlineHash.value(key);
    }
    return ret;
}


QString Pdu_NetJsonPack::getKey(const QString &ip, uchar addr)
{
    foreach (const auto &it, mHash.values()) {
        int src_addr = it->value("addr").toInt();
        QString src_ip = it->value("ip").toString();
        QString key = it->value("dev_key").toString();
        if((src_ip == ip) && (addr == src_addr)) return key;
    }
    return "";
}

bool Pdu_NetJsonPack::getByKey(const QString &key, QString &ip, uchar &addr)
{
    bool ret = mHash.contains(key);
    if(ret) {
        auto it = mHash.value(key);
        addr = it->value("addr").toInt();
        ip = it->value("ip").toString();
    }
    return ret;
}

void Pdu_NetJsonPack::append(const QString &key, const QString &ip, uchar addr)
{
    if(!mHash.contains(key)) {
        QSharedPointer<QJsonObject> jsonObj(new QJsonObject());
        jsonObj->insert("ip", ip); jsonObj->insert("status", 5);
        jsonObj->insert("addr", addr); jsonObj->insert("dev_key", key);
        QDateTime datetime = QDateTime::currentDateTime().addSecs(-60);
        jsonObj->insert("uptime", datetime.toString("yyyy-MM-dd hh:mm:ss"));
        mHash.insert(key, jsonObj);
    }
}

bool Pdu_NetJsonPack::remove(const QString &key)
{
    mHash.remove(key);
    return mOnlineHash.remove(key);
}

QString Pdu_NetJsonPack::toKey(const QString &ip, uchar addr)
{
    QString key = ip + "_" + QString::number(addr);
    return key;
}
