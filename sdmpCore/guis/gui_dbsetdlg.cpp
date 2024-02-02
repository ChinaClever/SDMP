/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_dbsetdlg.h"
#include "ui_gui_dbsetdlg.h"

Gui_DbSetDlg::Gui_DbSetDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Gui_DbSetDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    connect(this, &QDialog::accepted, this, &Gui_DbSetDlg::onAccepted);
}

Gui_DbSetDlg::~Gui_DbSetDlg()
{
    delete ui;
}

void Gui_DbSetDlg::getSqlUnit(int id)
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    sCfgSqlUnit *hda = nullptr, *ele = nullptr;
    switch (id) {
    case 0: hda = &it->room_hda, ele = &it->room_ele; break;
    case 1: hda = &it->aisle_hda, ele = &it->aisle_ele; break;
    case 2: hda = &it->cab_hda, ele = &it->cab_ele; break;
    case 3: hda = &it->rack_hda, ele = &it->rack_ele; break;
    case 4: hda = &it->pdu_hda, ele = &it->pdu_ele; break;
    case 5: hda = &it->bar_hda, ele = &it->bar_ele; break;
    case 6: hda = &it->box_hda, ele = &it->box_ele; break;
    default: cout << id; return;
    }m_hda = hda; m_ele=ele;
}

void Gui_DbSetDlg::setTitle(int id)
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

    str += tr("记录频率");
    ui->titleLab->setText(str);
}


void Gui_DbSetDlg::init(int id)
{
    getSqlUnit(id); setTitle(id);
    ui->eleSpinBox->setValue(m_ele->interval);
    ui->eleEnBox->setCurrentIndex(m_ele->en?1:0);
    ui->hdaSpinBox->setValue(m_hda->interval);
    ui->hdaEnBox->setCurrentIndex(m_hda->en?1:0);
}

void Gui_DbSetDlg::onAccepted()
{
    m_ele->en = ui->eleEnBox->currentIndex();
    m_ele->interval = ui->eleSpinBox->value();
    m_hda->en = ui->hdaEnBox->currentIndex();
    m_hda->interval = ui->hdaSpinBox->value();

    QMap<QString, QVariant> map;
    map.insert(m_ele->prefix+"en", m_ele->en);
    map.insert(m_hda->prefix+"en", m_hda->en);
    map.insert(m_ele->prefix+"interval", m_ele->interval);
    map.insert(m_hda->prefix+"interval", m_hda->interval);
    CfgCom::build()->writeCfg(map, "sql");
}
