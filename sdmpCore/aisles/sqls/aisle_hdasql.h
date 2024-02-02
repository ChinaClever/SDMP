#ifndef AISLE_HDASQL_H
#define AISLE_HDASQL_H
#include "aisle_elesql.h"

class Aisle_HdaSql : public OrmObj<AisleHdaModel>
{
    Aisle_HdaSql();
public:
    static Aisle_HdaSql *build();

    int workDown();
    AisleHdaModel aisleHda(uint id);
    QJsonObject aisleHdaJson(uint id);

private:
    void appendHda(const AisleHdaModel &model);
    AisleHdaModel aisleHdaByCab(uint aisleId);

private:
    Aisle_IndexSql *mIndexSql;
};

#endif // AISLE_HDASQL_H
