/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "aisle_hdasql.h"

Aisle_HdaSql::Aisle_HdaSql()
{

}


Aisle_HdaSql *Aisle_HdaSql::build()
{
    static Aisle_HdaSql* sington = nullptr;
    if(!sington) sington = new Aisle_HdaSql();
    return sington;
}
