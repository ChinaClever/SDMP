/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_mqttwid.h"
#include "ui_gui_mqttwid.h"

Gui_MqttWid::Gui_MqttWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_MqttWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
}

Gui_MqttWid::~Gui_MqttWid()
{
    delete ui;
}
