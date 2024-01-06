#ifndef CAB_BOXSQL_H
#define CAB_BOXSQL_H
#include "../models/cabhdamodel.h"

class Cab_BoxSql: public OrmObj<CabBoxModel>
{
    Cab_BoxSql();
public:
    static Cab_BoxSql *bulid();


};

#endif // CAB_BOXSQL_H
