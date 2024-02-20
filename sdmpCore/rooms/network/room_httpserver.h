#ifndef ROOM_HTTPSERVER_H
#define ROOM_HTTPSERVER_H
#include "../sqls/room_hdasql.h"
#include "cabinets/network/cab_httpserver.h"

class Room_HttpServer: public Cab_HttpServer
{
public:
    Room_HttpServer(QObject *parent);

private:
    void room_httpInit();
    void room_nameList();
    void room_number();
    void room_powerList();
    void room_eleList();
    void room_power();
    void room_ele();
};

#endif // ROOM_HTTPSERVER_H
