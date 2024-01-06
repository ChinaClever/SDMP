#ifndef PDU_INDEXSQL_H
#define PDU_INDEXSQL_H
#include "../models/pdulogmodel.h"
#include "../network/pdu_httpserver.h"

class Pdu_IndexSql : public OrmObj<PduIndexModel>
{
    explicit Pdu_IndexSql();
public:
    static Pdu_IndexSql *bulid();

    QString getKey(uint id);
    QStringList getkeys();
    uint getId(const QString &key);
    uint getId(const QString &ip, uchar addr);
    QString getKey(const QString &ip, uchar addr);
    QStringList getHashkeys() {return mKeyHash.keys();}

    void initFun();
    void syncNetPack();
private:
    void toNetPack();

private:
    QHash<QString, uint> mKeyHash;
    QHash<QString, PduIndexModel> mDeleteHash;
    Pdu_NetJsonPack *mNetJsonPack=nullptr;
};

#endif // PDU_INDEXSQL_H
