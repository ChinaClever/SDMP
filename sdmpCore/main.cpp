#include <QCoreApplication>
#include "pdus/models/pdu_eventsql.h"
// #include "commons/http/httpserverobj.h"
#include "pdu_httpserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Pdu_HttpServer *obj = new Pdu_HttpServer();
    obj->http_listen(43796);





    // HttpServerObj *obj = new HttpServerObj();


    return a.exec();
}
