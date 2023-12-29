#ifndef PDUALARMSQL_H
#define PDUALARMSQL_H
#include "pdualarmmodel.h"

class PduAlarmSql : public OrmObj<PduAlarmModel>
{
    PduAlarmSql();
public:
    static PduAlarmSql *bulid();
    void append(uint pdu_id, const QString &status, const QString &content);

private:
    void test();
};

#endif // PDUALARMSQL_H
