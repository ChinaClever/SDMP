#ifndef PDU_INDEXSQL_H
#define PDU_INDEXSQL_H
#include "pduindexmodel.h"

class Pdu_IndexSql : public OrmObj<PduIndexModel>
{
    explicit Pdu_IndexSql();
public:
    static Pdu_IndexSql *bulid();

    QStringList keys();

    void init();

protected:
    void test();
};

#endif // PDU_INDEXSQL_H
