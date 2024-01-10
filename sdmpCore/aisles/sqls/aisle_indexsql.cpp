/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_indexsql.h"

Aisle_IndexSql::Aisle_IndexSql()
{

}


Aisle_IndexSql *Aisle_IndexSql::build()
{
    static Aisle_IndexSql* sington = nullptr;
    if(!sington) sington = new Aisle_IndexSql();
    return sington;
}
