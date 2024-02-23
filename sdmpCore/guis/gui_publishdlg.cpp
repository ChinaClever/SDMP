/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_publishdlg.h"
#include "ui_gui_publishdlg.h"

Gui_PublishDlg::Gui_PublishDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Gui_PublishDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    connect(this, &QDialog::accepted, this, &Gui_PublishDlg::onAccepted);
}

Gui_PublishDlg::~Gui_PublishDlg()
{
    delete ui;
}


void Gui_PublishDlg::getUnit(int id)
{
    sCfgPublishItem *it = &CfgCom::build()->mCfgPublish;
    sCfgMqttUnit *unit = nullptr; switch (id) {
    case 0: unit = &it->room; break;
    case 1: unit = &it->aisle; break;
    case 2: unit = &it->cab; break;
    case 3: unit = &it->rack; break;
    case 4: unit = &it->pdu; break;
    case 5: unit = &it->busbar; break;
    default: cout << id; return;
    } m_unit = unit;
}

void Gui_PublishDlg::setTitle(int id)
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

    str += tr("的MQTT主题");
    ui->titleLab->setText(str);
}


void Gui_PublishDlg::init(int id)
{
    getUnit(id); setTitle(id);
    ui->topicEdit->setText(m_unit->topic);
    ui->spinBox->setValue(m_unit->interval);
    ui->enBox->setCurrentIndex(m_unit->en?1:0);
}

void Gui_PublishDlg::onAccepted()
{
    m_unit->en = ui->enBox->currentIndex();
    m_unit->interval = ui->spinBox->value();
    m_unit->topic = ui->topicEdit->text();

    QMap<QString, QVariant> map;
    map.insert(m_unit->prefix+"en", m_unit->en);
    map.insert(m_unit->prefix+"topic", m_unit->topic);
    map.insert(m_unit->prefix+"interval", m_unit->interval);
    CfgCom::build()->writeCfg(map, "publish");
}
