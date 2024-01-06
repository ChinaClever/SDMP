#include "mainwindow.h"
#include <QApplication>

#include "cabinets/sqls/cab_indexsql.h"
// #include "pdus/sqls/pdu_logsql.h"
// #include "pdu_httpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Pdu_HttpServer *obj = new Pdu_HttpServer();
    // obj->http_listen(43796);

    // Pdu_EleSql::bulid();

    // Cab_IndexSql::bulid();

    MainWindow w;
    w.show();
    return a.exec();
}
