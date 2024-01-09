#ifndef CAB_PDUSQL_H
#define CAB_PDUSQL_H
#include "cab_boxsql.h"

class Cab_PduSql : public OrmObj<CabPduModel>
{
    Cab_PduSql();
public:
    static Cab_PduSql *build();

    void initFun();
    bool getPdu(uint cab_id, CabPduModel &model);

private:
    QHash<uint, uint> mHash;
};

#endif // CAB_PDUSQL_H
