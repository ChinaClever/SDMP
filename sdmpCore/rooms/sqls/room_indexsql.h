#ifndef ROOM_INDEXSQL_H
#define ROOM_INDEXSQL_H
#include "../models/roomhdamodel.h"
#include "aisles/sqls/aisle_hdasql.h"

class Room_IndexSql : public OrmObj<RoomIndexModel>
{
    Room_IndexSql();
public:
    static Room_IndexSql *build();

    QList<uint> getIds();
    QList<uint> getAisleIds(uint id);
    uint getIdByName(const QString &name);
    QString getNameById(uint id);
    QStringList getNames();


};

#endif // ROOM_INDEXSQL_H
