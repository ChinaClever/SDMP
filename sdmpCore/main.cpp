#include <QCoreApplication>
#include "pdus/index/pduindexsql.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    PduIndexSql::bulid();



    return a.exec();
}
