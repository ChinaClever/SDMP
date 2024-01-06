#ifndef CAB_INDEXSQL_H
#define CAB_INDEXSQL_H
#include "cab_pdusql.h"

class Cab_IndexSql : public OrmObj<CabIndexModel>
{
    Cab_IndexSql();
public:
    static Cab_IndexSql *bulid();

    void syncFun();
    uchar is_pdu_box(uint id);
    int getIds(QList<uint> &pdu, QList<uint> &box);

private:
    bool isModified = true;
};

#endif // CAB_INDEXSQL_H
