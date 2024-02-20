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
    QTimer::singleShot(146,this,SLOT(initFunSlot()));
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
    //connect(tab, SIGNAL(itemDoubleSig(int)), this, SLOT(itemDoubleSlot(int)));
}

void Gui_RestWid::setTableRow(ComTableWid *tab, int row, const QString &name, const QString &api, const QString &param)
{
    QStringList listStr;
    listStr << name << api << param;
    tab->setTableRow(row, listStr);
}

void Gui_RestWid::initPduTab()
{
    ComTableWid *tab = mPduTab = new ComTableWid(ui->tabWidget->widget(4));
    QStringList header; header << tr("名称")<< tr("API") << tr("参数")<< tr("请求次数");
    tab->initTableWid(header, 0, ""); initColumnWidth(tab); int row = 0;

    QString name = tr("PDU设备列表");
    QString api = "/pdu/keys";
    QString param ="";
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


void Gui_RestWid::initFunSlot()
{
    initWidget();
    initPduTab();
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

