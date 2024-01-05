#ifndef CAB_HDASQL_H
#define CAB_HDASQL_H
#include "cabhdamodel.h"

class Cab_HdaSql: public OrmObj<CabHdaModel>
{
    Cab_HdaSql();
public:
    static Cab_HdaSql *bulid();
};

#endif // CAB_HDASQL_H
