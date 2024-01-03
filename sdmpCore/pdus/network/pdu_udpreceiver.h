#ifndef PDU_UDPRECEIVER_H
#define PDU_UDPRECEIVER_H
#include <QUdpSocket>
#include <QThreadPool>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtCore>

struct sUdpRcvItem
{
    quint16 senderPort;
    QHostAddress address;
    QByteArray datagram;
};

class Pdu_UdpReceiver : public QThread
{
public:
    explicit Pdu_UdpReceiver(QObject* parent = nullptr);
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
