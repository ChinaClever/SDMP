#ifndef PDU_MQTTPUBLISH_H
#define PDU_MQTTPUBLISH_H
#include "httpserverobj.h"
#include "pdu_netjsonpack.h"
#include "commons/mqtt/mqtt_publish.h"
#include "commons/print.h"

class Pdu_MqttPublish
{
public:
    Pdu_MqttPublish();
    void pdu_work();
    bool compareTime(sCfgMqttUnit *unit);

private:
    void pdu_online(const QStringList &lst, const QString &prefix);
    void pdu_alarm(const QStringList &lst, const QString &prefix);

protected:
    Mqtt_Publish *m_mqtt;
};

#endif // PDU_MQTTPUBLISH_H
