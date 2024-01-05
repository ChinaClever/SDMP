/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_hdasql.h"

Cab_HdaSql::Cab_HdaSql()
{

}

Cab_HdaSql *Cab_HdaSql::bulid()
{
    static Cab_HdaSql* sington = nullptr;
    if(!sington) sington = new Cab_HdaSql();
    return sington;
}
