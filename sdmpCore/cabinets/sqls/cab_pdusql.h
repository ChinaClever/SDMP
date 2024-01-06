#ifndef CAB_PDUSQL_H
#define CAB_PDUSQL_H
#include "cab_boxsql.h"

class Cab_PduSql : public OrmObj<CabPduModel>
{
    Cab_PduSql();
public:
    static Cab_PduSql *bulid();

    void initFun();
    bool getPdu(uint cab_id, uint &a_pdu, uint &b_pdu);

private:
    QHash<uint, uint> mHash;
};

#endif // CAB_PDUSQL_H
