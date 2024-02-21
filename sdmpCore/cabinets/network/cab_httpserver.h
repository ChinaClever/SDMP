#ifndef CAB_HTTPSERVER_H
#define CAB_HTTPSERVER_H
#include "cab_alarm.h"

class Cab_HttpServer: public Pdu_HttpServer
{
public:
    explicit Cab_HttpServer(QObject *parent = nullptr);

private:
    void cab_number();
    void cab_nameList();
    void cab_powerList();
    void cab_eleList();
    void cab_power();
    void cab_ele();
    void cab_init();
    QList<uint> cab_getIdByQuery(const QHttpServerRequest &request);
};

#endif // CAB_HTTPSERVER_H
