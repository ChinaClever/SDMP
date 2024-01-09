/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_boxsql.h"

Cab_BoxSql::Cab_BoxSql()
{

}

Cab_BoxSql *Cab_BoxSql::build()
{
    static Cab_BoxSql* sington = nullptr;
    if(!sington) sington = new Cab_BoxSql();
    return sington;
}
