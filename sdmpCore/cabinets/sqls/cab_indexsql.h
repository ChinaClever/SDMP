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
    uint roomId(uint id);

    QString getNameById(uint id);
    QList<uint> getIdsByRoom(uint room_id);
    QList<uint> getIdsByAisle(uint aisle_id);
    QList<uint> getIdsByRoomAisle(uint room_id, uint aisle_id);    
    QList<uint> getIdsByName(QList<uint> &id, const QString &name);
    uint getIdsByName(uint room_id, const QString &cab);
};

#endif // CAB_INDEXSQL_H
