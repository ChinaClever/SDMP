#ifndef CAB_HTTPSERVER_H
#define CAB_HTTPSERVER_H
#include "cab_alarm.h"

class Cab_HttpServer: public Pdu_HttpServer
{
public:
    explicit Cab_HttpServer(QObject *parent = nullptr);

private:
    void cab_init();
    void cab_list();
    void cab_data();
    void cab_datas();
    void cab_modified();

    QJsonObject cab_getData(uint id);
    QJsonArray cab_getIds();
};

#endif // CAB_HTTPSERVER_H
