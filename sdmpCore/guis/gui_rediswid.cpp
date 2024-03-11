/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_rediswid.h"
#include "ui_gui_rediswid.h"

Gui_RedisWid::Gui_RedisWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_RedisWid)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    groupBox_background_icon(this);
    mSetTableWid = new ComTableWid(ui->redisGroup);
    QTimer::singleShot(1450,this,SLOT(initFunSlot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
    connect(mSetTableWid, SIGNAL(itemDoubleSig(int)), this, SLOT(itemDoubleSlot(int)));
}

Gui_RedisWid::~Gui_RedisWid()
{
    delete ui;
}


void Gui_RedisWid::initCfg()
{
    sCfgRedisItem *it = &CfgCom::build()->mCfgRedis;
    ui->dbEnBox->setCurrentIndex(it->en?1:0);
    ui->portBox->setValue(it->port);
    ui->hostEdit->setText(it->host);
    ui->pwdEdit->setText(it->pwd);
    ui->dbBox->setValue(it->db);
}


void Gui_RedisWid::initSetTable()
{
    int id = 0;  QStringList header; header << tr("模块")
           << tr("使能") << tr("KEY") <<  tr("时间间隔");
    mSetTableWid->initTableWid(header, 5, "");
    mSetTableWid->setTableItem(id++, 0, tr("机房"));
    mSetTableWid->setTableItem(id++, 0, tr("柜列"));
    mSetTableWid->setTableItem(id++, 0, tr("机柜"));
    mSetTableWid->setTableItem(id++, 0, tr("机架"));
    mSetTableWid->setTableItem(id++, 0, tr("PDU"));
    mSetTableWid->setTableItem(id++, 0, tr("母线"));
    updateSetTable();
}


void Gui_RedisWid::updateSetTable()
{
    sCfgRedisUnit *unit = nullptr;
    sCfgRedisItem *it = &CfgCom::build()->mCfgRedis;
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
        mSetTableWid->setTableItem(i, 2, unit->key);
        str = tr("%1秒").arg(unit->interval);
        mSetTableWid->setTableItem(i, 3, str);
    }
}


void Gui_RedisWid::itemDoubleSlot(int row)
{
    Gui_RedisDlg dlg(this);
    dlg.init(row); dlg.exec();
    updateSetTable();
}


void Gui_RedisWid::initFunSlot()
{
    initCfg();
    initSetTable();
    timer->start(950);
}


void Gui_RedisWid::updateStatus()
{
    bool c = RedisClientCore::build()->isConnected();
    sCfgRedisItem *it = &CfgCom::build()->mCfgRedis;
    int status = 0; if(it->en) {
        if(c) status = 1; else status = 2;
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

void Gui_RedisWid::timeoutDone()
{
    sCfgRedisItem *unit = &CfgCom::mCfgRedis;
    RedisClientCore *redis = RedisClientCore::build();
    if(unit->en && !redis->isConnected()) {
        redis->connectHost(unit->host, unit->port, unit->pwd, unit->db);
    } updateStatus();
}


void Gui_RedisWid::saveCfg()
{
    CfgCom *cfg = CfgCom::build();
    sCfgRedisItem *it = &CfgCom::mCfgRedis;
    it->pwd = ui->pwdEdit->text().toLatin1();
    it->en = ui->dbEnBox->currentIndex();
    it->host = ui->hostEdit->text();
    it->port = ui->portBox->value();
    it->db = ui->dbBox->value();
    m_dbEditStatus = false;
    cfg->writeCfgRedis();
}


void Gui_RedisWid::on_redisEditBtn_clicked()
{
    if(m_dbEditStatus) {
        if(MsgBox::question(this, tr("是否保存修改信息?"))) saveCfg();
        ui->redisEditBtn->setText(tr("MQTT编辑"));
        ui->groupBox->setEnabled(false);
    } else {
        m_dbEditStatus = MsgBox::question(this, tr("是否修改MQTT配置信息?"));
        if(m_dbEditStatus) {
            ui->groupBox->setEnabled(true);
            ui->redisEditBtn->setText(tr("保存配置"));
        }
    }
}
