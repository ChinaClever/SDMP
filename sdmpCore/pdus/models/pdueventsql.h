#ifndef PDUEVENTSQL_H
#define PDUEVENTSQL_H
#include "pdueventmodel.h"

class PduEventSql : public OrmObj<PduEventModel>
{
    PduEventSql();
public:
    static PduEventSql *bulid();
    void append(uint pdu_id, const QString &type, const QString &content);

private:
    void test();
};

#endif // PDUEVENTSQL_H
