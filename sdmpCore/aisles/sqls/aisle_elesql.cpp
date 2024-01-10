/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_elesql.h"

Aisle_EleSql::Aisle_EleSql()
{
    mIndexSql = Aisle_IndexSql::build();
}


Aisle_EleSql *Aisle_EleSql::build()
{
    static Aisle_EleSql* sington = nullptr;
    if(!sington) sington = new Aisle_EleSql();
    return sington;
}


void Aisle_EleSql::workDown()
{
    QList<uint> idLst = mIndexSql->getIds();
    foreach (const auto &id, idLst) {
        QList<uint> cabLst = mIndexSql->getCabinetIds(id);
        foreach (const auto cab_id, cabLst) {


        }




    }

    // QList<uint> Cab_IndexSql::getIdsByAisle(uint aisle_id)
}
