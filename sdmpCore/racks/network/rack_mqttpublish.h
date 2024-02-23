#ifndef RACK_MQTTPUBLISH_H
#define RACK_MQTTPUBLISH_H
#include "rooms/network/room_httpserver.h"
#include "../sqls/rack_hdasql.h"

class Rack_MqttPublish : public Room_MqttPublish
{
public:
    Rack_MqttPublish();
    void rack_work();
};

#endif // RACK_MQTTPUBLISH_H
