#ifndef PDU_LOGSQL_H
#define PDU_LOGSQL_H
#include "pdu_hdasql.h"

class Pdu_LogSql : public OrmObj<PduLogModel>
{
    Pdu_LogSql();
public:
    static Pdu_LogSql *bulid();
    void workDown();

private:
    void initUdp();
    void http_post();
    void append(const QJsonObject &obj);
    void toJson(const QByteArray &datagram, const QString &ip);
    void test();

private:
    QMap<QString, QString> mLst;
};

#endif // PDU_LOGSQL_H
