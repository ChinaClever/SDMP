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
    timer = new QTimer(this);
    groupBox_background_icon(this); timer->start(3000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
}

Gui_MainWid::~Gui_MainWid()
{
    delete ui;
}

void Gui_MainWid::pduNum()
{
    Pdu_NetJsonPack *pdu = Pdu_NetJsonPack::build();
    int offline = pdu->offline_list().size();
    int online = pdu->online_list().size();
    int alarm = pdu->alarm_list().size();
    int number = pdu->keys().size();

    ui->numLab->setText(QString::number(number));
    ui->alarmLab->setText(QString::number(alarm));
    ui->onlineLab->setText(QString::number(online));
    ui->offlineLab->setText(QString::number(offline));
}

void Gui_MainWid::idcCnt()
{
    int v = Room_IndexSql::build()->getIds().size();
    ui->roomLab->setText(QString::number(v));

    v = Cab_IndexSql::build()->getIds().size();
    ui->cabLab->setText(QString::number(v));

    v = Aisle_IndexSql::build()->getIds().size();
    ui->aisleLab->setText(QString::number(v));

    v = Rack_IndexSql::build()->getIds().size();
    ui->rackLab->setText(QString::number(v));
}

void Gui_MainWid::netCnt()
{
    quint64 cnt = Pdu_NetJsonPack::build()->getCnt();
    QLocale locale; QString str = locale.toString(cnt);
    ui->netLab->setText(str);
}

void Gui_MainWid::convertSeconds(uint seconds, int& days, int& hours, int& minutes)
{
    const int SECONDS_PER_DAY = 24 * 60 * 60;
    const int SECONDS_PER_HOUR = 60 * 60;
    const int SECONDS_PER_MINUTE = 60;

    days = seconds / SECONDS_PER_DAY;
    seconds %= SECONDS_PER_DAY;

    hours = seconds / SECONDS_PER_HOUR;
    seconds %= SECONDS_PER_HOUR;

    minutes = seconds / SECONDS_PER_MINUTE;
}

void Gui_MainWid::secsUpdate()
{
    static uint sec = 0;
    sec += 3; int days, hours, minutes;
    convertSeconds(sec, days, hours, minutes);

    QString fmd = tr("%1天%2时%3分");
    QString str = fmd.arg(days).arg(hours).arg(minutes);
    ui->timeLab->setText(str);
}


void Gui_MainWid::timeoutDone()
{
    netCnt();
    pduNum();
    idcCnt();
    secsUpdate();
}
