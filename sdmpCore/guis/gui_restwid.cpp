/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_restwid.h"
#include "ui_gui_restwid.h"

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
    ui->httpUrlEdit->setEnabled(2==it->http.acl);

    ui->httpsEnBox->setCurrentIndex(it->https.en?1:0);
    ui->httpsAclBox->setCurrentIndex(it->https.acl);
    ui->httpsPortSpin->setValue(it->https.port);
    ui->httpsUrlEdit->setText(it->https.url);
    ui->httpsUrlEdit->setEnabled(2==it->https.acl);
}


void Gui_RestWid::initFunSlot()
{
    initWidget();
    initPduTab();
}

void  Gui_RestWid::saveCfg()
{

}

void Gui_RestWid::on_httpEditBtn_clicked()
{
    if(m_httpEditStatus) {
        if(MsgBox::question(this, tr("是否保存修改信息?"))) saveCfg();
        ui->httpWidget->setEnabled(false); ui->httpEditBtn->setText(tr("数据库编辑"));
    } else {
        m_httpEditStatus = MsgBox::question(this, tr("是否修改数据库配置信息?"));
        if(m_httpEditStatus) {
            ui->httpWidget->setEnabled(true);
            ui->httpEditBtn->setText(tr("保存配置"));
        }
    }
}

