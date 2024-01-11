#ifndef ROOM_INDEXSQL_H
#define ROOM_INDEXSQL_H
#include "../models/roomhdamodel.h"


class Room_IndexSql : public OrmObj<RoomIndexModel>
{
    Room_IndexSql();
public:
    static Room_IndexSql *build();

};

#endif // ROOM_INDEXSQL_H
