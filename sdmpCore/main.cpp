#include <QCoreApplication>
#include "pdus/models/pdueventsql.h"
#include "commons/http/httpserverobj.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    PduEventSql::bulid();







    // HttpServerObj *obj = new HttpServerObj();


    return a.exec();
}
