#ifndef AISLE_HTTPSERVER_H
#define AISLE_HTTPSERVER_H

#include "../sqls/aisle_hdasql.h"
#include "cabinets/network/cab_httpserver.h"

class Aisle_HttpServer : public Cab_HttpServer
{
public:
    explicit Aisle_HttpServer(QObject *parent = nullptr);

};

#endif // AISLE_HTTPSERVER_H
