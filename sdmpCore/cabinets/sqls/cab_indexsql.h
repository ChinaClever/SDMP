#ifndef CAB_INDEXSQL_H
#define CAB_INDEXSQL_H
#include "cab_pdusql.h"

class Cab_IndexSql : public OrmObj<CabIndexModel>
{
    Cab_IndexSql();
public:
    static Cab_IndexSql *build();

    QList<uint> getIds();
    uchar is_pdu_box(uint id);
    int getIds(QList<uint> &pdu, QList<uint> &box);
    double pow_capacity(uint id);
    int is_disabled(uint id);

    QList<uint> getIdsByAisle(uint aisle_id);

};

#endif // CAB_INDEXSQL_H
