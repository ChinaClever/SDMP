#ifndef PDUELESQL_H
#define PDUELESQL_H
#include "pduelemodel.h"

class PduEleSql: public OrmObj<PduEleModel>
{
    PduEleSql();
public:
    static PduEleSql *bulid();
    void append(uint pdu_id, uchar type, uchar indexes, double value);

private:
    void test();
};

#endif // PDUELESQL_H
