#ifndef AISLE_HTTPSERVER_H
#define AISLE_HTTPSERVER_H
#include "aisle_mqttpublish.h"

class Aisle_HttpServer : public Cab_HttpServer
{
public:
    explicit Aisle_HttpServer(QObject *parent = nullptr);

private:
    void aisle_number();
    void aisle_httpInit();
    void aisle_nameList();
    void aisle_powerList();
    void aisle_eleList();
    void aisle_power();
    void aisle_ele();
};

#endif // AISLE_HTTPSERVER_H
