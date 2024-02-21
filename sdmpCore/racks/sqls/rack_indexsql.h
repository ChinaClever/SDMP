#ifndef RACK_INDEXSQL_H
#define RACK_INDEXSQL_H
#include "../models/rackhdamodel.h"
#include "rooms/sqls/room_hdasql.h"

class Rack_IndexSql: public OrmObj<RackIndexModel>
{
    Rack_IndexSql();
public:
    static Rack_IndexSql *build();

    QList<uint> getIds();
    QJsonObject outletByRack(uint id);
    uint a_port(uint id);
    uint b_port(uint id);

    QString getNameById(uint id);
    QList<uint> getIdsByCab(uint cab_id);
    QList<uint> getIdsByName(uint cab_id, const QString &name);
};

#endif // RACK_INDEXSQL_H
