#ifndef PDU_ALARMSQL_H
#define PDU_ALARMSQL_H
#include "pdualarmmodel.h"

class Pdu_AlarmSql : public OrmObj<PduAlarmModel>
{
    Pdu_AlarmSql();
public:
    static Pdu_AlarmSql *bulid();
    void append(uint pdu_id, const QString &status, const QString &content);

private:
    void test();
};

#endif // PDU_ALARMSQL_H
