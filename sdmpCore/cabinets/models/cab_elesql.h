#ifndef CAB_ELESQL_H
#define CAB_ELESQL_H
#include "cabelemodel.h"

class Cab_EleSql: public OrmObj<CabEleModel>
{
    Cab_EleSql();
public:
    static Cab_EleSql *bulid();


};

#endif // CAB_ELESQL_H
