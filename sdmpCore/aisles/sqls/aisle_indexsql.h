#ifndef AISLE_INDEXSQL_H
#define AISLE_INDEXSQL_H
#include "aisle_barsql.h"

class Aisle_IndexSql : public OrmObj<AisleIndexModel>
{
    Aisle_IndexSql();
public:
    static Aisle_IndexSql *build();



};

#endif // AISLE_INDEXSQL_H
