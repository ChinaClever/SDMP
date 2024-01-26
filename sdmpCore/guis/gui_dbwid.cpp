/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_dbwid.h"
#include "ui_gui_dbwid.h"

Gui_DbWid::Gui_DbWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_DbWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
}

Gui_DbWid::~Gui_DbWid()
{
    delete ui;
}
