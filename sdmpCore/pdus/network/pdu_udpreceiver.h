#ifndef PDU_UDPRECEIVER_H
#define PDU_UDPRECEIVER_H
#include "commons/print.h"
#include <QJsonDocument>
#include <QThreadPool>
#include <QJsonObject>
#include <QUdpSocket>
#include <QtCore>

struct sUdpRcvItem
{
    quint16 senderPort;
    QHostAddress address;
    QByteArray datagram;
};

class Pdu_UdpReceiver : public QThread
{
    explicit Pdu_UdpReceiver(QObject* parent = nullptr);
public:
    static Pdu_UdpReceiver *build(QObject* parent = nullptr);
    bool get(QSharedPointer<sUdpRcvItem> &it);
    ~Pdu_UdpReceiver();

private:
    void run();
    void workDown();
    bool initSocket(int port);

private:
    bool isRun = false;
    QUdpSocket *mSocket = nullptr;
    QQueue<QSharedPointer<sUdpRcvItem>> mQueue;
};

#endif // PDU_UDPRECEIVER_H
