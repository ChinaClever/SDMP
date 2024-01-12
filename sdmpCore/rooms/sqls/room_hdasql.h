#ifndef ROOM_HDASQL_H
#define ROOM_HDASQL_H
#include "room_elesql.h"

class Room_HdaSql: public OrmObj<RoomHdaModel>
{
    Room_HdaSql();
public:
    static Room_HdaSql *build();
    RoomHdaModel roomHda(uint id);
    QJsonObject roomHdaJson(uint id);
    void hdaWork();

private:
    void appendHda(const RoomHdaModel &model);

private:
    Room_IndexSql *mIndexSql;
};

#endif // ROOM_HDASQL_H
