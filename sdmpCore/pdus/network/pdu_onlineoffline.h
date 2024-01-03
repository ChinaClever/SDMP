#ifndef PDU_ONLINEOFFLINE_H
#define PDU_ONLINEOFFLINE_H
#include "pdu_netjsonpack.h"

class Pdu_OnlineOffline : public QThread
{    
    Q_OBJECT
    Pdu_OnlineOffline(QObject* parent = nullptr);
public:
    static Pdu_OnlineOffline *bulid(QObject* parent = nullptr);
    QStringList online_list();
    QStringList offline_list();
    ~Pdu_OnlineOffline();

signals:
    void pdu_online_offline_sig(const QString &key, bool statue);

protected:
    void run();
    void online_offline_update();

private slots:
    void onTimeout() {start();}

private:
    bool isRun=false;
    QTimer *mTimer = nullptr;
    QHash<QString, bool> mOnHash;
};

#endif // PDU_ONLINEOFFLINE_H
