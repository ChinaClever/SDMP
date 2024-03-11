#ifndef AISLE_MQTTPUBLISH_H
#define AISLE_MQTTPUBLISH_H
#include "aisle_redisclient.h"

class Aisle_MqttPublish : public Cab_MqttPublish
{
public:
    Aisle_MqttPublish();
    void aisle_work();
};

#endif // AISLE_MQTTPUBLISH_H
