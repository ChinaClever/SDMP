#ifndef PDU_NETJSONPACK_H
#define PDU_NETJSONPACK_H

#include "pdu_udpreceiver.h"
#include <QtConcurrent>

class Pdu_NetJsonPack : public QThread
{
    Q_OBJECT
    explicit Pdu_NetJsonPack(QObject* parent = nullptr);
public:
    static Pdu_NetJsonPack *build(QObject* parent = nullptr);
    auto get() {return &mHash;}
    ~Pdu_NetJsonPack();

    QJsonValue getJsonObject(const QString &dev, const QString &key);
    QSharedPointer<QJsonObject> shredPointer(const QString &key);
    QJsonObject meta(const QString &key);
    QJsonValue dev(const QString &key);
    QJsonValue line(const QString &key);
    QJsonValue loop(const QString &key);
    QJsonValue group(const QString &key);
    QJsonValue outlet(const QString &key);
    QJsonValue env(const QString &key);
    QJsonValue tg(const QString &key);
    QString alarm(const QString &key);
    QJsonObject alarms();

    quint64 getCnt() {return mCnt;}
    bool remove(const QString &key);
    void append(const QString &key, const QString &ip, uchar addr);
    bool getByKey(const QString &key, QString &ip, uchar &addr);
    QString getKey(const QString &ip, uchar addr);
    QString toKey(const QString &ip, uchar addr);
    QStringList keys() {return mHash.keys();}
    bool is_online(const QString &key);
    QStringList online_list();
    QStringList offline_list();
    QStringList alarm_list();

signals:
    void online_offline_sig(const QString &key, bool statue);

private:
    void run();
    bool workDown();
    void online_offline_update();
    void toJson(QByteArray &datagram, const QString &ip);

private slots:
    void timeoutDone();
    void onTimeout();// {QtConcurrent::run([&]{online_offline_update();});}

private:
    quint64 mCnt = 0;
    bool isRun = true;
    QTimer *timer = nullptr;
    Pdu_UdpReceiver *mUdp=nullptr;
    QHash<QString, bool> mOnlineHash;
    QHash<QString, QSharedPointer<QJsonObject>> mHash;
};

#endif // PDU_NETJSONPACK_H
