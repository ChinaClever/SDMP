#ifndef ROOM_ELESQL_H
#define ROOM_ELESQL_H
#include "room_indexsql.h"

class Room_EleSql: public OrmObj<RoomEleModel>
{
    Room_EleSql();
public:
    static Room_EleSql *build();
};

#endif // ROOM_ELESQL_H
