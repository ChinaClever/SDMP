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
    timer = new QTimer(this);
    Mqtt_Client::bulid(this);
    groupBox_background_icon(this);
    mSetTableWid = new ComTableWid(ui->publishGroup);
    QTimer::singleShot(1450,this,SLOT(initFunSlot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
    connect(mSetTableWid, SIGNAL(itemDoubleSig(int)), this, SLOT(itemDoubleSlot(int)));
    Mqtt_Publish::bulid(this);
}

Gui_MqttWid::~Gui_MqttWid()
{
    delete ui;
}


void Gui_MqttWid::initCfg()
{
    sCfgMqttItem *it = &CfgCom::build()->mCfgMqtt;
    ui->dbEnBox->setCurrentIndex(it->type);
    ui->qosCombo->setCurrentIndex(it->qos);
    ui->spinBox->setValue(it->keepAlive);
    ui->idEdit->setText(it->clientId);
    ui->pathEdit->setText(it->path);
    ui->userEdit->setText(it->usr);
    ui->portBox->setValue(it->port);
    ui->urlEdit->setText(it->url);
    ui->pwdEdit->setText(it->pwd);
}


void Gui_MqttWid::initSetTable()
{
    int id = 0;  QStringList header; header << tr("模块")
           << tr("使能") << tr("发布主题") <<  tr("时间间隔");
    mSetTableWid->initTableWid(header, 5, "");
    mSetTableWid->setTableItem(id++, 0, tr("机房"));
    mSetTableWid->setTableItem(id++, 0, tr("柜列"));
    mSetTableWid->setTableItem(id++, 0, tr("机柜"));
    mSetTableWid->setTableItem(id++, 0, tr("机架"));
    mSetTableWid->setTableItem(id++, 0, tr("PDU"));
    mSetTableWid->setTableItem(id++, 0, tr("母线"));
    updateSetTable();
}


void Gui_MqttWid::updateSetTable()
{
    sCfgMqttUnit *unit = nullptr;
    sCfgPublishItem *it = &CfgCom::build()->mCfgPublish;
    int row = mSetTableWid->rowCount(); int alarm=0;
    QString str; for(int i=0; i<row; ++i) {
        switch (i) {
        case 0: unit = &it->room; break;
        case 1: unit = &it->aisle; break;
        case 2: unit = &it->cab; break;
        case 3: unit = &it->rack; break;
        case 4: unit = &it->pdu; break;
        case 5: unit = &it->busbar; break;
        default: break;
        }

        if(unit->en) { alarm=0; str = tr("启用");
        } else { str = tr("禁用"); alarm=1;}
        mSetTableWid->setTableItem(i, 1, str);
        //mSetTableWid->setItemColor(i, 1, alarm);
        mSetTableWid->setTableItem(i, 2, unit->topic);
        str = tr("%1秒").arg(unit->interval);
        mSetTableWid->setTableItem(i, 3, str);
    }
}

void  Gui_MqttWid::itemDoubleSlot(int row)
{
    Gui_PublishDlg dlg(this);
    dlg.init(row); dlg.exec();
    updateSetTable();
}


void Gui_MqttWid::initFunSlot()
{
    initCfg();
    initSetTable();
    timer->start(950);
}


void Gui_MqttWid::updateStatus()
{
    sCfgMqttItem *it = &CfgCom::build()->mCfgMqtt;
    int status = 0; if(it->type) {
        if(it->isConnected) status = 1;
        else status = 2;
    }

    QString style, str = tr("---"); switch (status) {
    case 1: str = tr("正常"); style = "background-color:green; color:rgb(255, 255, 255);"; break;
    case 2: str = tr("错误"); style = "background-color:red; color:rgb(255, 255, 255);"; break;
    case 3: str = tr("禁用"); style = "background-color:yellow; color:rgb(0, 0, 0);"; break;
    default: style = "background-color: transparent; color: black;"; break;
    }

    style += "font:100 34pt \"微软雅黑\";";
    ui->statusLab->setStyleSheet(style);
    ui->statusLab->setText(str);
}

void Gui_MqttWid::timeoutDone()
{
    updateStatus();
}


void Gui_MqttWid::saveCfg()
{
    CfgCom *cfg = CfgCom::build();
    sCfgMqttItem *it = &cfg->mCfgMqtt;
    it->clientId = ui->idEdit->text();
    it->path = ui->pathEdit->text();
    it->url = ui->urlEdit->text();
    it->keepAlive = ui->spinBox->value();
    it->qos = ui->qosCombo->currentIndex();
    it->usr = ui->userEdit->text().toLatin1();
    it->pwd = ui->pwdEdit->text().toLatin1();
    it->type = ui->dbEnBox->currentIndex();
    it->port = ui->portBox->value();
    cfg->writeCfgMqtt(); m_dbEditStatus = false;
    Mqtt_Client::bulid(this)->startMqtt();
}


void Gui_MqttWid::on_mqttEditBtn_clicked()
{
    if(m_dbEditStatus) {
        if(MsgBox::question(this, tr("是否保存修改信息?"))) saveCfg();
        ui->mqttEditBtn->setText(tr("MQTT编辑"));
        ui->groupBox->setEnabled(false);
    } else {
        m_dbEditStatus = MsgBox::question(this, tr("是否修改MQTT配置信息?"));
        if(m_dbEditStatus) {
            ui->groupBox->setEnabled(true);
            ui->mqttEditBtn->setText(tr("保存配置"));
        }
    }
}


void Gui_MqttWid::on_dbEnBox_currentIndexChanged(int index)
{    
    bool hidden = true;
    int port = 0; switch (index) {
    case 1: port = 1883; break;
    case 2: port = 8883; break;
    case 3: port = 8083; hidden = false; break;
    case 4: port = 8084; hidden = false; break;
    }

    ui->label_2->setHidden(hidden);
    ui->pathEdit->setHidden(hidden);
    if(port) ui->portBox->setValue(port);
}

