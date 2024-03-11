/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_redisdlg.h"
#include "ui_gui_redisdlg.h"

Gui_RedisDlg::Gui_RedisDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Gui_RedisDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    connect(this, &QDialog::accepted, this, &Gui_RedisDlg::onAccepted);
}

Gui_RedisDlg::~Gui_RedisDlg()
{
    delete ui;
}


void Gui_RedisDlg::getUnit(int id)
{
    sCfgRedisItem *it = &CfgCom::build()->mCfgRedis;
    sCfgRedisUnit *unit = nullptr; switch (id) {
    case 0: unit = &it->room; break;
    case 1: unit = &it->aisle; break;
    case 2: unit = &it->cab; break;
    case 3: unit = &it->rack; break;
    case 4: unit = &it->pdu; break;
    case 5: unit = &it->busbar; break;
    default: cout << id; return;
    } m_unit = unit;
}

void Gui_RedisDlg::setTitle(int id)
{
    QString str; switch (id) {
    case 0: str = tr("机房"); break;
    case 1: str = tr("柜列"); break;
    case 2: str = tr("机柜"); break;
    case 3: str = tr("机架"); break;
    case 4: str = tr("PDU"); break;
    case 5: str = tr("母线"); break;
    case 6: str = tr("插接箱"); break;
    default: cout << id; return;
    }

    str += tr("的Key");
    ui->titleLab->setText(str);
}


void Gui_RedisDlg::init(int id)
{
    getUnit(id); setTitle(id);
    ui->topicEdit->setText(m_unit->key);
    ui->spinBox->setValue(m_unit->interval);
    ui->enBox->setCurrentIndex(m_unit->en?1:0);
}


void Gui_RedisDlg::onAccepted()
{
    m_unit->en = ui->enBox->currentIndex();
    m_unit->interval = ui->spinBox->value();
    m_unit->key = ui->topicEdit->text();

    QMap<QString, QVariant> map;
    map.insert(m_unit->prefix+"en", m_unit->en);
    map.insert(m_unit->prefix+"key", m_unit->key);
    map.insert(m_unit->prefix+"interval", m_unit->interval);
    CfgCom::build()->writeCfg(map, "redis");
}
