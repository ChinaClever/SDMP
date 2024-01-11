#ifndef ROOM_HDASQL_H
#define ROOM_HDASQL_H
#include "room_elesql.h"

class Room_HdaSql: public OrmObj<RoomHdaModel>
{
    Room_HdaSql();
public:
    static Room_HdaSql *build();
};

#endif // ROOM_HDASQL_H
