/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_indexsql.h"

Pdu_IndexSql::Pdu_IndexSql()
{
    // test();
}



Pdu_IndexSql *Pdu_IndexSql::bulid()
{
    static Pdu_IndexSql* sington = nullptr;
    if(!sington)  sington = new Pdu_IndexSql();
    return sington;
}

void Pdu_IndexSql::init()
{
    fetch_all();

}


void Pdu_IndexSql::test()
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
