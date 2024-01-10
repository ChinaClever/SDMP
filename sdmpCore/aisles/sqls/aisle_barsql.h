#ifndef AISLE_BARSQL_H
#define AISLE_BARSQL_H
#include "../models/aislehdamodel.h"

class Aisle_BarSql : public OrmObj<AisleBarModel>
{
    Aisle_BarSql();
public:
    static Aisle_BarSql *build();

    void initFun();
    bool getPdu(uint aisle_id, AisleBarModel &model);

private:
    QHash<uint, uint> mHash;
};

#endif // AISLE_BARSQL_H
