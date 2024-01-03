/*
 *  UDP接收类无需关心，由Pdu_NetJsonPack类自动创建并启动线程工作
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_udpreceiver.h"

Pdu_UdpReceiver::Pdu_UdpReceiver(QObject *parent) : QThread(parent)
{
    isRun = initSocket(6002);
    if(isRun) this->start();
}


Pdu_UdpReceiver::~Pdu_UdpReceiver()
{
    isRun = false; wait();
    mSocket->close();
}

bool Pdu_UdpReceiver::get(QSharedPointer<sUdpRcvItem> &it)
{
    bool ret = true;

    if(mQueue.size()) {
        it = mQueue.dequeue();
    } else {
        ret = false;
    }

    return ret;
}

bool Pdu_UdpReceiver::initSocket(int port)
{
    bool ret = true; if(!mSocket) {
        mSocket = new QUdpSocket(this);
        ret = mSocket->bind(QHostAddress::Any, port);
        if(!ret) qDebug() << "Faeild to bind UDP socket";
    }
    return ret;
}

void Pdu_UdpReceiver::workDown()
{
    QSharedPointer<sUdpRcvItem> it(new sUdpRcvItem);
    it->datagram.resize(mSocket->pendingDatagramSize());
    int len = mSocket->readDatagram(it->datagram.data(), it->datagram.size(), &it->address, &it->senderPort);
    if(len > 0)  mQueue.enqueue(it);
    //qDebug() << "Received datagram from" << it->address.toString() << ":" << it->senderPort;
    //qDebug() << "Data:" << it->datagram;
}

void Pdu_UdpReceiver::run()
{    
    while(isRun) {
        if(mSocket->hasPendingDatagrams()) {
            workDown();
        } else QThread::msleep(1);
    }
}
