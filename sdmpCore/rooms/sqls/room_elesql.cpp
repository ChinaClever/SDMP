/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_elesql.h"

Room_EleSql::Room_EleSql()
{

}


Room_EleSql *Room_EleSql::build()
{
    static Room_EleSql* sington = nullptr;
    if(!sington) sington = new Room_EleSql();
    return sington;
}
