#ifndef ROOM_MQTTPUBLISH_H
#define ROOM_MQTTPUBLISH_H
#include "room_redisclient.h"

class Room_MqttPublish : public Aisle_MqttPublish
{
public:
    Room_MqttPublish();
    void room_work();
};

#endif // ROOM_MQTTPUBLISH_H
