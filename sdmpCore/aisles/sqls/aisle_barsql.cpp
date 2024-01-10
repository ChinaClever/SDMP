/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_barsql.h"

Aisle_BarSql::Aisle_BarSql()
{

}


Aisle_BarSql *Aisle_BarSql::build()
{
    static Aisle_BarSql* sington = nullptr;
    if(!sington) sington = new Aisle_BarSql();
    return sington;
}
