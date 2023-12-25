#ifndef PDUINDEXSQL_H
#define PDUINDEXSQL_H
#include "pduindexmodel.h"

class PduIndexSql : public OrmObj<PduIndexModel>
{
    explicit PduIndexSql();
public:
    static PduIndexSql *bulid();


};

#endif // PDUINDEXSQL_H
