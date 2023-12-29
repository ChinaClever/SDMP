/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pduindexsql.h"

PduIndexSql::PduIndexSql()
{
    // test();
}



PduIndexSql *PduIndexSql::bulid()
{
    static PduIndexSql* sington = nullptr;
    if(!sington)  sington = new PduIndexSql();
    return sington;
}


void PduIndexSql::test()
{
    QList<PduIndexModel> itLst;
    for(int i = 0;i < 5;i ++) {
        PduIndexModel it;
        it.uid = QString ("lzy %1").arg(i);
        it.ip = "123456";
        it.cascade_num = 0;
        itLst.append(it);
    }
    cout << delete_all() << count() << mListModel.size();

    cout;
    save(itLst);
    cout;
    save(itLst);

    qDebug()  << count() <<  fetch_all() << mListModel.size() ;
}
