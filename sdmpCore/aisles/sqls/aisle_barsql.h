#ifndef AISLE_BARSQL_H
#define AISLE_BARSQL_H
#include "../models/aislehdamodel.h"


class Aisle_BarSql : public OrmObj<AisleBarModel>
{
    Aisle_BarSql();
public:
    static Aisle_BarSql *build();

};

#endif // AISLE_BARSQL_H
