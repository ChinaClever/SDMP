/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_indexsql.h"

Cab_IndexSql::Cab_IndexSql()
{

}



Cab_IndexSql *Cab_IndexSql::bulid()
{
    static Cab_IndexSql* sington = nullptr;
    if(!sington) sington = new Cab_IndexSql();
    return sington;
}
