#include <QCoreApplication>
#include "pdus/models/pdu_logsql.h"
#include "pdu_httpserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Pdu_HttpServer *obj = new Pdu_HttpServer();
    obj->http_listen(43796);

    Pdu_EleSql::bulid();







    return a.exec();
}
