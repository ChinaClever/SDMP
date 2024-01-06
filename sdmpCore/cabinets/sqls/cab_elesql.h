#ifndef CAB_ELESQL_H
#define CAB_ELESQL_H
#include "cab_indexsql.h"
#include "pdus/sqls/pdu_logsql.h"

class Cab_EleSql: public OrmObj<CabEleModel>
{
    Cab_EleSql();
public:
    static Cab_EleSql *bulid();

    void workDown();
    QJsonObject cabEle(uint cab_id);


private:
    void cabPduEle(uint cab_id);
    QJsonObject cabJsonPduEle(uint cab_id);
    bool pduTgEle(uint pdu_id, double &ele);

private:
    Cab_PduSql *mPduSql;
    Cab_IndexSql *mIndexSql;
};

#endif // CAB_ELESQL_H
