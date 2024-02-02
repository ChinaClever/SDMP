#ifndef RACK_HDASQL_H
#define RACK_HDASQL_H
#include "rack_elesql.h"

class Rack_HdaSql: public OrmObj<RackHdaModel>
{
    Rack_HdaSql();
public:
    static Rack_HdaSql *build();
    RackHdaModel rackHda(uint rackId);
    QJsonObject rackHdaJson(uint id);
    int workDown();


private:
    bool a_outlet(uint rack_id, RackHdaModel &model);
    bool b_outlet(uint rack_id, RackHdaModel &model);
    void appendHda(const RackHdaModel &model);

private:
    Rack_IndexSql *mIndexSql;
};

#endif // RACK_HDASQL_H
