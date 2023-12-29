#ifndef PDUHDASQL_H
#define PDUHDASQL_H
#include "pduhdamodel.h"

class PduHdaSql : public OrmObj<PduHdaModel>
{
    PduHdaSql();
public:
    static PduHdaSql *bulid();
    void append(uint pdu_id, uchar type, uchar topic, uchar indexes, double value);

private:
    void test();
};

#endif // PDUHDASQL_H
