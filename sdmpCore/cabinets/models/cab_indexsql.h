#ifndef CAB_INDEXSQL_H
#define CAB_INDEXSQL_H
#include "cabindexmodel.h"

class Cab_IndexSql : public OrmObj<CabIndexModel>
{
    Cab_IndexSql();
public:
    static Cab_IndexSql *bulid();


};

#endif // CAB_INDEXSQL_H
