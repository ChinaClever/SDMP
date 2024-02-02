#ifndef AISLE_ELESQL_H
#define AISLE_ELESQL_H
#include "aisle_indexsql.h"

class Aisle_EleSql : public OrmObj<AisleEleModel>
{
    Aisle_EleSql();
public:
    static Aisle_EleSql *build();

    int workDown();
    AisleEleModel aisleEle(uint id);
    QJsonObject aisleEleJson(uint id);

private:
    void appendEle(const AisleEleModel &model);
    AisleEleModel aisleEleByCab(uint aisleId);

private:
    Aisle_IndexSql *mIndexSql;
};

#endif // AISLE_ELESQL_H
