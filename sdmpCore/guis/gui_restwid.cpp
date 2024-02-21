/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_restwid.h"
#include "ui_gui_restwid.h"
#include "commons/print.h"

Gui_RestWid::Gui_RestWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_RestWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(1346,this,SLOT(initFunSlot()));
}

Gui_RestWid::~Gui_RestWid()
{
    delete ui;
}

void Gui_RestWid::initColumnWidth(ComTableWid *tab)
{
    tab->setColumnWidth(0, 280);
    tab->setColumnWidth(1, 300);
    tab->setColumnWidth(2, 280);
    tab->setColumnWidth(3, 40);
}

void Gui_RestWid::setTableRow(ComTableWid *tab, int row, const QString &name, const QString &api,
                              const QString &param)
{
    QStringList listStr;
    listStr << name << api << param;
    tab->setTableRow(row, listStr);
}

void Gui_RestWid::initPduTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(4));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数"); //<< tr("返回");
    tab->initTableWid(header, 0, ""); int row = 0; //initColumnWidth(tab);

    QString name = tr("PDU设备列表");
    QString api = "/pdu/key/list";
    QString param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU报警列表"); api = "/pdu/alarm/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU在线列表"); api = "/pdu/online/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU离线列表"); api = "/pdu/offline/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU数量统计"); api = "/pdu/number"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU所有数据"); api = "/pdu/meta"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU数据包"); api = "/pdu/data"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU的统计数据"); api = "/pdu/tg"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU的相数据"); api = "/pdu/line"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU的回路数据"); api = "/pdu/loop"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU的输出位数据"); api = "/pdu/outlet"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("PDU的环境数据"); api = "/pdu/env"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("key与IP对应表"); api = "/pdu/key/to/ip/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("根据key获取IP地址"); api = "/pdu/key/by/ip"; param ="key=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("根据IP获取数据"); api = "/pdu/data/by/ip"; param ="ip=?,addr=?";
    setTableRow(tab, row++, name, api, param);
}

void Gui_RestWid::initWidget()
{
    sCfgRestItem *it = &CfgCom::build(this)->mCfgRest;
    ui->httpEnBox->setCurrentIndex(it->http.en?1:0);
    ui->httpAclBox->setCurrentIndex(it->http.acl);
    ui->httpPortSpin->setValue(it->http.port);
    ui->httpUrlEdit->setText(it->http.url);

    ui->httpsEnBox->setCurrentIndex(it->https.en?1:0);
    ui->httpsAclBox->setCurrentIndex(it->https.acl);
    ui->httpsPortSpin->setValue(it->https.port);
    ui->httpsUrlEdit->setText(it->https.url);
}

void Gui_RestWid::initRoomTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(0));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数");
    tab->initTableWid(header, 0, ""); int row = 0;

    QString name = tr("机房名称列表");
    QString api = "/room/name/list";
    QString param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("机房数量统计"); api = "/room/number"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("机房功率列表"); api = "/room/power/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("机房电能列表"); api = "/room/ele/list"; param ="";
    setTableRow(tab, row++, name, api, param);

    name = tr("机房当前功率"); api = "/room/power"; param ="room=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机房当前电能"); api = "/room/ele"; param ="room=?";
    setTableRow(tab, row++, name, api, param);
}

void Gui_RestWid::initAisleTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(1));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数");
    tab->initTableWid(header, 0, ""); int row = 0;

    QString name = tr("柜列名称列表");
    QString api = "/aisle/name/list";
    QString param ="room=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("柜列数量统计"); api = "/aisle/number"; param ="room=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("柜列功率列表"); api = "/aisle/power/list"; param ="room=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("柜列电能列表"); api = "/aisle/ele/list"; param ="room=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("柜列当前功率"); api = "/aisle/power"; param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("柜列当前电能"); api = "/aisle/ele"; param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);
}


void Gui_RestWid::initCabinetTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(2));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数");
    tab->initTableWid(header, 0, ""); int row = 0;

    QString name = tr("机柜名称列表");
    QString api = "/cabinet/name/list";
    QString param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机柜数量统计"); api = "/cabinet/number"; param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机柜功率列表"); api = "/cabinet/power/list"; param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机柜电能列表"); api = "/cabinet/ele/list"; param ="room=?,aisle=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机柜当前功率"); api = "/cabinet/power"; param ="room=?,aisle=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("机柜当前电能"); api = "/cabinet/ele"; param ="room=?,aisle=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);
}

void Gui_RestWid::initRackTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(3));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数");
    tab->initTableWid(header, 0, ""); int row = 0;

    QString name = tr("U位名称列表");
    QString api = "/rack/name/list";
    QString param ="room=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("U位数量统计"); api = "/rack/number"; param ="room=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("U位功率列表"); api = "/rack/power/list"; param ="room=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("U位电能列表"); api = "/rack/ele/list"; param ="room=?,cabinet=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("U位当前功率"); api = "/rack/power"; param ="room=?,cabinet=?,rack=?";
    setTableRow(tab, row++, name, api, param);

    name = tr("U位当前电能"); api = "/rack/ele"; param ="room=?,cabinet=?,rack=?";
    setTableRow(tab, row++, name, api, param);
}

void Gui_RestWid::initFunSlot()
{
    initWidget();
    initPduTab();
    initRoomTab();
    initAisleTab();
    initCabinetTab();
    initHttpStatus();
    initRackTab();
}

void Gui_RestWid::saveCfg(sCfgRestUnit *it)
{
    QMap<QString, QVariant> map;
    map.insert(it->prefix+"en", it->en);
    map.insert(it->prefix+"acl", it->acl);
    map.insert(it->prefix+"url", it->url);
    map.insert(it->prefix+"port", it->port);
    CfgCom::build()->writeCfg(map, "rest");
}

void Gui_RestWid::saveHttpCfg()
{
    sCfgRestUnit *it = &CfgCom::mCfgRest.http;
    it->en = ui->httpEnBox->currentIndex();
    it->port = ui->httpPortSpin->value();
    it->acl = ui->httpAclBox->currentIndex();
    it->url = ui->httpUrlEdit->text();

    if(2!=it->acl) return;
    if(cm_isIPaddress(it->url)) saveCfg(it);
    else MsgBox::critical(this, tr("HTTP指定IP格式错误"));
}

void Gui_RestWid::on_httpEditBtn_clicked()
{
    if(m_httpEditStatus) {
        if(MsgBox::question(this, tr("是否保存HTTP修改信息?"))) saveHttpCfg();
        ui->httpWidget->setEnabled(false); ui->httpEditBtn->setText(tr("HTTP编辑"));
    } else {
        m_httpEditStatus = MsgBox::question(this, tr("是否修改HTTP配置信息?"));
        if(m_httpEditStatus) {
            ui->httpWidget->setEnabled(true);
            ui->httpEditBtn->setText(tr("保存HTTP配置"));
        }
    }
}

void Gui_RestWid::initHttpStatus()
{
    DbThreadCore *core = DbThreadCore::build();
    int status = core->http_listen_status();
    if(status) updateStatus(status, ui->httpStatusLab);

    status = core->https_listen_status();
    if(status) updateStatus(status, ui->httpsStatusLab);
}


void Gui_RestWid::updateStatus(int status, QLabel *lab)
{
    QString style, str = tr("---"); switch (status) {
    case 1: str = tr("正常"); style = "background-color:green; color:rgb(255, 255, 255);"; break;
    case 2: str = tr("错误"); style = "background-color:red; color:rgb(255, 255, 255);"; break;
    case 0: str = tr("禁用"); style = "background-color:yellow; color:rgb(0, 0, 0);"; break;
    default:  break;
    }

    style += "font:100 34pt \"微软雅黑\";";
    lab->setStyleSheet(style);
    lab->setText(str);
}



void Gui_RestWid::on_httpAclBox_currentIndexChanged(int index)
{
    ui->httpUrlEdit->setHidden(2!=index);
    ui->label_4->setHidden(2!=index);
}

void  Gui_RestWid::saveHttpsCfg()
{
    sCfgRestUnit *it = &CfgCom::mCfgRest.https;
    it->en = ui->httpsEnBox->currentIndex();
    it->port = ui->httpsPortSpin->value();
    it->acl = ui->httpsAclBox->currentIndex();
    it->url = ui->httpsUrlEdit->text();

    if(2!=it->acl) return;
    if(cm_isIPaddress(it->url)) saveCfg(it);
    else MsgBox::critical(this, tr("HTTPS指定IP格式错误"));
}


void Gui_RestWid::on_httpsEditBtn_clicked()
{
    if(m_httpsEditStatus) {
        if(MsgBox::question(this, tr("是否保存HTTPS修改信息?"))) saveHttpsCfg();
        ui->httpsWidget->setEnabled(false); ui->httpsEditBtn->setText(tr("HTTPS编辑"));
    } else {
        m_httpsEditStatus = MsgBox::question(this, tr("是否修改HTTPS配置信息?"));
        if(m_httpsEditStatus) {
            ui->httpsWidget->setEnabled(true);
            ui->httpsEditBtn->setText(tr("保存HTTPS配置"));
        }
    }
}


void Gui_RestWid::on_httpsAclBox_currentIndexChanged(int index)
{
    ui->httpsUrlEdit->setHidden(2!=index);
    ui->label_8->setHidden(2!=index);
}

