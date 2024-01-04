/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_logsql.h"
#include "http.h"

Pdu_LogSql::Pdu_LogSql()
{
    initUdp();
    // test();
}


Pdu_LogSql *Pdu_LogSql::bulid()
{
    static Pdu_LogSql* sington = nullptr;
    if(!sington) sington = new Pdu_LogSql();
    return sington;
}

void Pdu_LogSql::initUdp()
{
    static QUdpSocket *udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::Any, 514);
    QObject::connect(udpSocket, &QUdpSocket::readyRead, [&]() {
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram; QHostAddress sender; quint16 senderPort;
            datagram.resize(udpSocket->pendingDatagramSize());
            int rtn = udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            if(rtn > 0) toJson(datagram, sender.toString().remove("::ffff:"));
            //qDebug() << "Received datagram from" << sender.toString() << ":" << senderPort;
            //qDebug() << "Data:" << datagram;
        }
    });
}

void Pdu_LogSql::toJson(const QByteArray &datagram, const QString &ip)
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
                cout<< "log datagram error"; return ;
            } append(jsonObj); mLst.insert(uid, datagram);
        } else {
            cout << "JSON document is not an object";
        }
    } else {
        cout << "Failed to parse JSON";
    }
}


void Pdu_LogSql::append(const QJsonObject &obj)
{
    ModelPtr it(addModel());
    QString uuid = getString(obj, "uuid");
    uint pdu_id = Pdu_IndexSql::bulid()->getId(uuid);
    if(pdu_id) {
        it->pdu_id = pdu_id;
        it->content = getString(obj, "content");
        it->state_type = getString(obj, "state_type");
        it->alarm_event = getData(obj, "alarm_event");
        mLstIts.append(it);
    } else cout << "pdu id error" << uuid;
}


void Pdu_LogSql::http_post()
{
    QUrl url("https://some.domain.url/");
    auto reply = Http::instance().post(url, mLst);
    QObject::connect(reply, &HttpReply::finished, [&](auto &reply) {
        if (reply.isSuccessful()) {
            mLst.clear(); qDebug() << "Feel the bytes!" << reply.body();
        } else {
            cout << "Something's wrong here" << reply.statusCode() << reply.reasonPhrase();
        }
    });
}

void Pdu_LogSql::workDown()
{
    if(mLstIts.size()) insert();
    if(mLst.size()) http_post();
}


void Pdu_LogSql::test()
{
    // for(int i=0; i<5; ++i) {
    //     append(i, "1","2");
    // }insert();
}
