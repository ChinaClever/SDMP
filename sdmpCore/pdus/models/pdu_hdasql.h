#ifndef PDU_HDASQL_H
#define PDU_HDASQL_H
#include "pduhdamodel.h"

class Pdu_HdaSql : public OrmObj<PduHdaModel>
{
    Pdu_HdaSql();
public:
    static Pdu_HdaSql *bulid();
    void append(uint pdu_id, uchar type, uchar topic, uchar indexes, double value);

private:
    void test();
};

#endif // PDU_HDASQL_H
