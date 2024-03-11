/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mqttpublishcore.h"

MqttPublishCore::MqttPublishCore(QObject *parent)
    : QThread{parent}
{

}

MqttPublishCore::~MqttPublishCore()
{
    isRun = false;
    wait();
}

void MqttPublishCore::workDown()
{
    if(isRun) room_work();
    if(isRun) aisle_work();
    if(isRun) cab_work();
    if(isRun) pdu_work();
    if(isRun) rack_work();
}


void MqttPublishCore::start_work()
{
    sCfgMqttItem *unit = &CfgCom::mCfgMqtt;
    if(unit->type && isRun && unit->isConnected) workDown();
}

void MqttPublishCore::run()
{
    while(isRun) {
        sleep(1);
        start_work();
    }
}
