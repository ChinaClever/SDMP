#ifndef RACK_ELESQL_H
#define RACK_ELESQL_H
#include "rack_indexsql.h"

class Rack_EleSql: public OrmObj<RackEleModel>
{
    Rack_EleSql();
public:
    static Rack_EleSql *build();
    RackEleModel rackEle(uint rackId);
    QJsonObject rackEleJson(uint id);
    void eleWork();

private:
    double a_outlet(uint rack_id);
    double b_outlet(uint rack_id);
    void appendEle(const RackEleModel &model);

private:
    Rack_IndexSql *mIndexSql;
};

#endif // RACK_ELESQL_H
