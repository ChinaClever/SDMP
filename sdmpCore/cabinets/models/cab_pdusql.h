#ifndef CAB_PDUSQL_H
#define CAB_PDUSQL_H
#include "cabpdumodel.h"

class Cab_PduSql : public OrmObj<CabPduModel>
{
    Cab_PduSql();
public:
    static Cab_PduSql *bulid();

};

#endif // CAB_PDUSQL_H
