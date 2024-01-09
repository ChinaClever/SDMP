#ifndef CAB_ALARM_H
#define CAB_ALARM_H
#include "../sqls/cab_hdasql.h"

class Cab_Alarm
{
    Cab_Alarm();
public:
    static Cab_Alarm *build();

    void alarmWork();
private:
    void http_post(const QJsonObject &obj);
};

#endif // CAB_ALARM_H
