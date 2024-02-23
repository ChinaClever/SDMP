/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mqttpublishcore.h"

MqttPublishCore::MqttPublishCore()
{

}

MqttPublishCore::~MqttPublishCore()
{

}

void MqttPublishCore::workDown()
{
    room_work();
    aisle_work();
    cab_work();
    pdu_work();
    rack_work();
}


void MqttPublishCore::start_work()
{    
    static QTime t = QTime::currentTime();
    QTime c = QTime::currentTime();
    QTime s = t.addSecs(1);
    if(c > s) {
        workDown();
        t = c; //cout << isRun;
    }
}
