#ifndef RACK_HDASQL_H
#define RACK_HDASQL_H
#include "rack_elesql.h"

class Rack_HdaSql: public OrmObj<RackHdaModel>
{
    Rack_HdaSql();
public:
    static Rack_HdaSql *build();


};

#endif // RACK_HDASQL_H
