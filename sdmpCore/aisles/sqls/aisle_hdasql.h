#ifndef AISLE_HDASQL_H
#define AISLE_HDASQL_H
#include "aisle_elesql.h"

class Aisle_HdaSql : public OrmObj<AisleHdaModel>
{
    Aisle_HdaSql();
public:
    static Aisle_HdaSql *build();
};

#endif // AISLE_HDASQL_H
