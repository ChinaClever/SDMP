/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_elesql.h"

Aisle_EleSql::Aisle_EleSql()
{

}


Aisle_EleSql *Aisle_EleSql::build()
{
    static Aisle_EleSql* sington = nullptr;
    if(!sington) sington = new Aisle_EleSql();
    return sington;
}
