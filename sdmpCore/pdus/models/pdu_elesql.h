#ifndef PDU_ELESQL_H
#define PDU_ELESQL_H
#include "pduelemodel.h"

class Pdu_EleSql: public OrmObj<PduEleModel>
{
    Pdu_EleSql();
public:
    static Pdu_EleSql *bulid();
    void append(uint pdu_id, uchar type, uchar indexes, double value);

private:
    void test();
};

#endif // PDU_ELESQL_H
