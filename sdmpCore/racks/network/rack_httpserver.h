#ifndef RACK_HTTPSERVER_H
#define RACK_HTTPSERVER_H
#include "rack_mqttpublish.h"

class Rack_HttpServer : public Room_HttpServer
{
public:
    explicit Rack_HttpServer(QObject *parent = nullptr);

private:
    void rack_number();
    void rack_nameList();
    void rack_powerList();
    void rack_eleList();
    void rack_power();
    void rack_ele();
    void rack_init();
    QList<uint> rack_getIdByQuery(const QHttpServerRequest &request);
};

#endif // RACK_HTTPSERVER_H
