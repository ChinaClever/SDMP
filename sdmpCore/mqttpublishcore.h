#ifndef MQTTPUBLISHCORE_H
#define MQTTPUBLISHCORE_H
#include "redisclientcore.h"

class MqttPublishCore : public QThread, public Rack_MqttPublish
{
public:
     explicit MqttPublishCore(QObject *parent = nullptr);
    ~MqttPublishCore();

protected:
    void run();
    void workDown();
    void start_work();

private:
    bool isRun=true;
};

#endif // MQTTPUBLISHCORE_H
