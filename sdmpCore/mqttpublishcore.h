#ifndef MQTTPUBLISHCORE_H
#define MQTTPUBLISHCORE_H
#include "racks/network/rack_httpserver.h"

class MqttPublishCore : public Rack_MqttPublish
{
public:
     MqttPublishCore();
    ~MqttPublishCore();
    void start_work();
    void workDown();
};

#endif // MQTTPUBLISHCORE_H
