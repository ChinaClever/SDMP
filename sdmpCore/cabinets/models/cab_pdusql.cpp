/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_pdusql.h"

Cab_PduSql::Cab_PduSql()
{

}


Cab_PduSql *Cab_PduSql::bulid()
{
    static Cab_PduSql* sington = nullptr;
    if(!sington) sington = new Cab_PduSql();
    return sington;
}

