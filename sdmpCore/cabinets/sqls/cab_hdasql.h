#ifndef CAB_HDASQL_H
#define CAB_HDASQL_H
#include "cab_elesql.h"

class Cab_HdaSql: public OrmObj<CabHdaModel>
{
    Cab_HdaSql();
public:
    static Cab_HdaSql *build();

    int workDown();
    CabHdaModel cabHda(uint cab_id);
    QJsonObject cabHdaJson(uint cab_id);
    double tgApparentPower(uint cab_id);


private:
    bool pduHda(uint pdu_id, double &apparent_power, double &active_power);
    QJsonObject cabJsonPduHda(uint cab_id);
    void cabPduHda(uint cab_id);

private:
    Cab_PduSql *mPduSql;
    Cab_IndexSql *mIndexSql;
};

#endif // CAB_HDASQL_H
