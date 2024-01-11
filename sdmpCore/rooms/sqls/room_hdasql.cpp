/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_hdasql.h"

Room_HdaSql::Room_HdaSql()
{

}

Room_HdaSql *Room_HdaSql::build()
{
    static Room_HdaSql* sington = nullptr;
    if(!sington) sington = new Room_HdaSql();
    return sington;
}
