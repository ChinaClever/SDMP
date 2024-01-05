/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_elesql.h"

Cab_EleSql::Cab_EleSql()
{

}

Cab_EleSql *Cab_EleSql::bulid()
{
    static Cab_EleSql* sington = nullptr;
    if(!sington) sington = new Cab_EleSql();
    return sington;
}
