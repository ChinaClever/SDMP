/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduindexsql.h"

PduIndexSql::PduIndexSql()
{
    // qx::QxSqlQuery query("select * from " + tableName() );




    QList<PduIndexModel> aList;
    for(int i = 0;i < 5000;i ++)
    {
        PduIndexModel user;
        user.age =  10;
        user.name = QString ("jiangtao %1").arg(i);
        aList.append(user);
    }
    delete_all();
    qDebug() << count();

    cout;
    save(aList);

    cout;
    fetch_all();
    cout;

    qDebug() << mListModel.size();

}



PduIndexSql *PduIndexSql::bulid()
{
    static PduIndexSql* sington = nullptr;
    if(!sington)  sington = new PduIndexSql();
    return sington;
}
