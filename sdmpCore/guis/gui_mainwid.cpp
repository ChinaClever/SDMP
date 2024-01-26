/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_mainwid.h"
#include "ui_gui_mainwid.h"

Gui_MainWid::Gui_MainWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);

}

Gui_MainWid::~Gui_MainWid()
{
    delete ui;
}
