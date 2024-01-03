#ifndef PDU_EVENTSQL_H
#define PDU_EVENTSQL_H
#include "pdueventmodel.h"

class Pdu_EventSql : public OrmObj<PduEventModel>
{
    Pdu_EventSql();
public:
    static Pdu_EventSql *bulid();
    void append(uint pdu_id, const QString &type, const QString &content);

private:
    void test();
};

#endif // PDU_EVENTSQL_H
