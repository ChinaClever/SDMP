#ifndef PDUINDEXSQL_H
#define PDUINDEXSQL_H
#include "pduindexmodel.h"

class PduIndexSql : public OrmObj<PduIndexModel>
{
    explicit PduIndexSql();
public:
    static PduIndexSql *bulid();


protected:
    void test();
};

#endif // PDUINDEXSQL_H
