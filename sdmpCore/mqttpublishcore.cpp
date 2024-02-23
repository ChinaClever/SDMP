/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mqttpublishcore.h"

MqttPublishCore::MqttPublishCore()
{

}


void MqttPublishCore::workDown()
{
    room_work();
    aisle_work();
    cab_work();
    pdu_work();
    rack_work();
    isRun = false;
}

void MqttPublishCore::start_work()
{
    if(isRun) return ; else isRun = true;
    QtConcurrent::run([&]{workDown();});
}
