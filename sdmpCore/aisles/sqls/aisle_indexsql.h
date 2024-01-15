#ifndef AISLE_INDEXSQL_H
#define AISLE_INDEXSQL_H
#include "aisle_barsql.h"
#include "cabinets/sqls/cab_hdasql.h"

class Aisle_IndexSql : public OrmObj<AisleIndexModel>
{
    Aisle_IndexSql();
public:
    static Aisle_IndexSql *build();

    QList<uint> getIds();
    QList<uint> getIdsByRoom(uint id);
    QList<uint> getCabinetIds(uint id);
    int pdu_bar(uint id);

};

#endif // AISLE_INDEXSQL_H
