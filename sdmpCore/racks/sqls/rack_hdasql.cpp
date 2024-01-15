/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "rack_hdasql.h"

Rack_HdaSql::Rack_HdaSql()
{

}

Rack_HdaSql *Rack_HdaSql::build()
{
    static Rack_HdaSql* sington = nullptr;
    if(!sington) sington = new Rack_HdaSql();
    return sington;
}
