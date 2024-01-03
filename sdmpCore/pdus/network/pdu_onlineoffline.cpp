/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_onlineoffline.h"

Pdu_OnlineOffline::Pdu_OnlineOffline(QObject *parent) : QThread(parent)
{
    mTimer = new QTimer(this); mTimer->start(3500);
    connect(mTimer, &QTimer::timeout, this, &Pdu_OnlineOffline::onTimeout);
}

Pdu_OnlineOffline *Pdu_OnlineOffline::bulid(QObject* parent)
{
    static Pdu_OnlineOffline* sington = nullptr;
    if(!sington) sington = new Pdu_OnlineOffline(parent);
    return sington;
}


Pdu_OnlineOffline::~Pdu_OnlineOffline()
{
    isRun = false;
    wait();
}


QStringList Pdu_OnlineOffline::offline_list()
{
    QStringList lst;
    foreach (const auto &key, mOnHash.keys()) {
        if(!mOnHash.value(key)) lst << key;
    }
    return lst;
}


QStringList Pdu_OnlineOffline::online_list()
{
    QStringList lst;
    foreach (const auto &key, mOnHash.keys()) {
        if(mOnHash.value(key)) lst << key;
    }
    return lst;
}

void Pdu_OnlineOffline::online_offline_update()
{
    QHash<QString, QSharedPointer<QJsonObject>> *hash;
    hash = Pdu_NetJsonPack::bulid()->get(); QString str = "uptime";
    foreach (const auto &it, hash->values()) {
        if(it->contains(str)) {
            QString key = it->value("uuid").toString();
            QDateTime overtime = QDateTime::currentDateTime().addSecs(-12);
            QDateTime uptime = QDateTime::fromString(it->value(str).toString(), "yyyy-MM-dd hh:mm:ss");
            if(uptime >= overtime) {
                if(mOnHash.contains(key) && (mOnHash[key] != true)) {
                    emit pdu_online_offline_sig(key, true);
                } mOnHash[key] = true;
            } else {
                if(mOnHash.contains(key) && mOnHash[key] != false) {
                    emit pdu_online_offline_sig(key, false);
                    it->insert("status", 5); it->insert("pdu_alarm", "Offline");
                } mOnHash[key] = false;
            }
        }
    }
}

void Pdu_OnlineOffline::run()
{
    if(isRun) return; else isRun = true;
    online_offline_update();
    isRun = false;
}
