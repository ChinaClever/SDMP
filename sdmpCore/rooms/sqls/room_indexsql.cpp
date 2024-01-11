/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "room_indexsql.h"

Room_IndexSql::Room_IndexSql()
{

}


Room_IndexSql *Room_IndexSql::build()
{
    static Room_IndexSql* sington = nullptr;
    if(!sington) sington = new Room_IndexSql();
    return sington;
}
