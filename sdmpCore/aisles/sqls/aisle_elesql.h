#ifndef AISLE_ELESQL_H
#define AISLE_ELESQL_H
#include "aisle_indexsql.h"

class Aisle_EleSql : public OrmObj<AisleEleModel>
{
    Aisle_EleSql();
public:
    static Aisle_EleSql *build();

    void workDown();

private:
    Aisle_IndexSql *mIndexSql;
};

#endif // AISLE_ELESQL_H
