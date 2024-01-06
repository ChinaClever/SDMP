#ifndef CAB_INDEXSQL_H
#define CAB_INDEXSQL_H
#include "../models/cabhdamodel.h"

class Cab_IndexSql : public OrmObj<CabIndexModel>
{
    Cab_IndexSql();
public:
    static Cab_IndexSql *bulid();

    void initFun();
    uchar is_pdu_box(uint id);
    int getIds(QList<uint> &pdu, QList<uint> &box);

private:

};

#endif // CAB_INDEXSQL_H
