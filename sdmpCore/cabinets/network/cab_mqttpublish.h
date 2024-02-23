#ifndef CAB_MQTTPUBLISH_H
#define CAB_MQTTPUBLISH_H
#include "../sqls/cab_hdasql.h"

class Cab_MqttPublish : public Pdu_MqttPublish
{
public:
    Cab_MqttPublish();
    void cab_work();
};

#endif // CAB_MQTTPUBLISH_H
