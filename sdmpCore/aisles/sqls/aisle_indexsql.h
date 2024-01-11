#ifndef AISLE_INDEXSQL_H
#define AISLE_INDEXSQL_H
#include "aisle_barsql.h"
#include "cabinets/sqls/cab_hdasql.h"

class Aisle_IndexSql : public OrmObj<AisleIndexModel>
{
    Aisle_IndexSql();
public:
    static Aisle_IndexSql *build();

    void syncFun();
    QList<uint> getIds();
    QList<uint> getCabinetIds(uint id);
    void set() {isModified = true;}
    int pdu_bar(uint id);



private:
    bool isModified = true;
};

#endif // AISLE_INDEXSQL_H
