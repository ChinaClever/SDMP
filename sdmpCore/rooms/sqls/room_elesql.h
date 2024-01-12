#ifndef ROOM_ELESQL_H
#define ROOM_ELESQL_H
#include "room_indexsql.h"

class Room_EleSql: public OrmObj<RoomEleModel>
{
    Room_EleSql();
public:
    static Room_EleSql *build();
    RoomEleModel roomEle(uint id);
    QJsonObject roomEleJson(uint id);
    void eleWork();

private:
    void appendEle(const RoomEleModel &model);

private:
    Room_IndexSql *mIndexSql;
};

#endif // ROOM_ELESQL_H
