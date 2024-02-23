/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "gui_dbwid.h"
#include "ui_gui_dbwid.h"
#include <QSqlDatabase>

Gui_DbWid::Gui_DbWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Gui_DbWid)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    groupBox_background_icon(this);
    QTimer::singleShot(2450,this,SLOT(initFunSlot()));
    mCntTableWid = new ComTableWid(ui->tabWidget->widget(0));
    mSetTableWid = new ComTableWid(ui->tabWidget->widget(1));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutDone()));
    connect(mSetTableWid, SIGNAL(itemDoubleSig(int)), this, SLOT(itemDoubleSlot(int)));
}

Gui_DbWid::~Gui_DbWid()
{
    delete ui;
}

void Gui_DbWid::initCfg()
{
    sCfgDbItem *it = &CfgCom::build()->mCfgDb;
    ui->dbDriverBox->addItems(QSqlDatabase::drivers());
    ui->dbDriverBox->setCurrentText(it->driver);
    ui->dbEnBox->setCurrentIndex(it->en?1:0);
    ui->dbPrefixEdit->setText(it->prefix);
    ui->dbUserEdit->setText(it->user);
    ui->dbNameEdit->setText(it->name);
    ui->dbPortBox->setValue(it->port);
    ui->dbHostEdit->setText(it->host);
    ui->dbPwdEdit->setText(it->pwd);
}

void Gui_DbWid::initCntTable()
{
    int id = 0; timer->start(950);
    QStringList header; header << tr("模块")
           << tr("历史数据条目数") <<  tr("历史数据记录总条数")
           << tr("电能条目数") <<  tr("电能记录总条数");
    mCntTableWid->initTableWid(header, 6, "");
    mCntTableWid->setTableItem(id++, 0, tr("机房"));
    mCntTableWid->setTableItem(id++, 0, tr("柜列"));
    mCntTableWid->setTableItem(id++, 0, tr("机柜"));
    mCntTableWid->setTableItem(id++, 0, tr("机架"));
    mCntTableWid->setTableItem(id++, 0, tr("PDU"));
    mCntTableWid->setTableItem(id++, 0, tr("母线"));
    mCntTableWid->setTableItem(id++, 0, tr("BOX"));
}

void Gui_DbWid::initSetTable()
{
    int id = 0;  QStringList header; header << tr("模块")
           << tr("电能记录") <<  tr("电能间隔(小时)")
           << tr("数据记录") <<  tr("数据间隔(分钟)");
    mSetTableWid->initTableWid(header, 6, "");
    mSetTableWid->setTableItem(id++, 0, tr("机房"));
    mSetTableWid->setTableItem(id++, 0, tr("柜列"));
    mSetTableWid->setTableItem(id++, 0, tr("机柜"));
    mSetTableWid->setTableItem(id++, 0, tr("机架"));
    mSetTableWid->setTableItem(id++, 0, tr("PDU"));
    mSetTableWid->setTableItem(id++, 0, tr("母线"));
    mSetTableWid->setTableItem(id++, 0, tr("BOX"));
    updateSetTable();
}

void Gui_DbWid::updateSetTable()
{
    sCfgSqlItem *it = &CfgCom::build()->mCfgSql;
    sCfgSqlUnit *hda = nullptr, *ele = nullptr;
    int row = mSetTableWid->rowCount(); int alarm=0;
    QString str; for(int i=0; i<row; ++i) {
        switch (i) {
        case 0: hda = &it->room_hda, ele = &it->room_ele; break;
        case 1: hda = &it->aisle_hda, ele = &it->aisle_ele; break;
        case 2: hda = &it->cab_hda, ele = &it->cab_ele; break;
        case 3: hda = &it->rack_hda, ele = &it->rack_ele; break;
        case 4: hda = &it->pdu_hda, ele = &it->pdu_ele; break;
        case 5: hda = &it->bar_hda, ele = &it->bar_ele; break;
        case 6: hda = &it->box_hda, ele = &it->box_ele; break;
        default: break;
        }

        if(ele->en) { alarm=0; str = tr("记录");
        } else { str = tr("不记录"); alarm=1;}
        mSetTableWid->setTableItem(i, 1, str);
        //mSetTableWid->setItemColor(i, 1, alarm);
        str = tr("%1小时").arg(ele->interval);
        mSetTableWid->setTableItem(i, 2, str);

        if(hda->en) { alarm=0; str = tr("记录");
        } else { str = tr("不记录"); alarm=1;}
        mSetTableWid->setTableItem(i, 3, str);
        //mSetTableWid->setItemColor(i, 3, alarm);
        str = tr("%1分钟").arg(hda->interval);
        mSetTableWid->setTableItem(i, 4, str);
    }
}

void  Gui_DbWid::itemDoubleSlot(int row)
{
    Gui_DbSetDlg dlg(this);
    dlg.init(row); dlg.exec();
    updateSetTable();
}

void Gui_DbWid::initFunSlot()
{
    initCfg(); initCntTable(); initSetTable();
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
    if(OrmDb::isOpen()) {
        updateStatus(0); insertTextSlot(tr("数据打开成功"), true);
    } else if(CfgCom::build()->mCfgDb.en) {
        updateStatus(2); insertTextSlot(tr("数据打开错误"), false);
    } else updateStatus(3);
}


void Gui_DbWid::setTextColor(bool pass)
{
    QColor color("black");
    updateStatus(pass?0:2);
    if(!pass) color = QColor("red");
    ui->textEdit->moveCursor(QTextCursor::Start);

    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(color);// 前景色(即字体色)设为color色
    QTextCursor cursor = ui->textEdit->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textEdit->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
}

void Gui_DbWid::insertTextSlot(const QString &msg, bool pass)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString t  = dt.toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString fmd = QString::number(++mId) + "、[%1] %2\n";
    setTextColor(pass); ui->textEdit->insertPlainText(fmd.arg(t, msg));
    if (ui->textEdit->document()->blockCount() > 500) {  // 检查文本行数是否超过 500 行
        for(int i=0; i<100; ++i) {
            QTextCursor cursor(ui->textEdit->document());    // 将光标移动到最后一行
            cursor.movePosition(QTextCursor::End);
            cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();  // 删除最后一行
        } // if(mId > 200) {mId=0; ui->textEdit->clear();}
    }
}

void Gui_DbWid::updateStatus(int status)
{
    QString style, str = tr("---"); switch (status) {
    case 0: str = tr("正常"); style = "background-color:green; color:rgb(255, 255, 255);"; break;
    case 1: str = tr("写入"); style = "background-color:yellow; color:rgb(0, 0, 0);"; break;
    case 2: str = tr("错误"); style = "background-color:red; color:rgb(255, 255, 255);"; break;
    case 3: str = tr("禁用"); style = "background-color:yellow; color:rgb(0, 0, 0);"; break;
    default:  break;
    }

    style += "font:100 34pt \"微软雅黑\";";
    ui->statusLab->setStyleSheet(style);
    ui->statusLab->setText(str);
}


void Gui_DbWid::setTableItem(int id, int column, quint64 number)
{
    QLocale locale(QLocale::English); // 使用英文地区的设置
    QString str = locale.toString(number);
    mCntTableWid->setTableItem(id, column, str);
}

void Gui_DbWid::updateDbCnt()
{
    static int w = 0;
    OrmDb *hda=nullptr, *ele=nullptr;
    int row = mCntTableWid->rowCount() + 1;
    int id =  (w++)%row; switch (id) {
    case 0: hda = Room_HdaSql::build(); ele = Room_EleSql::build(); break;
    case 1: hda = Aisle_HdaSql::build(); ele = Aisle_EleSql::build(); break;
    case 2: hda = Cab_HdaSql::build(); ele = Cab_EleSql::build(); break;
    case 3: hda = Rack_HdaSql::build(); ele = Rack_EleSql::build(); break;
    case 4: hda = Pdu_HdaSql::build(); ele = Pdu_EleSql::build(); break;
    default: return;
    }

    quint64 cnt = hda->get_cnt(); setTableItem(id, 1, cnt);
    cnt = hda->get_max_id(); setTableItem(id, 2, cnt);
    cnt = ele->get_cnt(); setTableItem(id, 3, cnt);
    cnt = ele->get_max_id(); setTableItem(id, 4, cnt);
}


void Gui_DbWid::timeoutDone()
{
    if(!CfgCom::mCfgDb.en){updateStatus(3); return;}
    else if(OrmDb::isOpen() && CfgCom::mCfgDb.en) {
        bool isWrite = DbThreadCore::build()->writing();
        int status = 0; if(isWrite) status = 1;
        updateStatus(status);
        updateDbCnt();
    }

    QStringList lst = OrmDb::sql_error();
    foreach (const auto &msg, lst) {
        insertTextSlot(msg, false);
    }

    lst = DbThreadCore::build()->writeMsg();
    foreach (const auto &msg, lst) {
        insertTextSlot(msg, true);
    }
}

void Gui_DbWid::saveCfg()
{
    CfgCom *cfg = CfgCom::build();
    sCfgDbItem *it = &cfg->mCfgDb;
    it->driver = ui->dbDriverBox->currentText();
    it->prefix = ui->dbPrefixEdit->text();
    it->host = ui->dbHostEdit->text();
    it->name = ui->dbNameEdit->text();
    it->user = ui->dbUserEdit->text();
    it->pwd = ui->dbPwdEdit->text();
    it->port = ui->dbPortBox->value();
    it->en = ui->dbEnBox->currentIndex();
    cfg->writeCfgDb(); m_dbEditStatus = false;
}


void Gui_DbWid::on_dbEditBtn_clicked()
{
    if(m_dbEditStatus) {
        if(MsgBox::question(this, tr("是否保存修改信息?"))) saveCfg();
        ui->dbEnBox->setEnabled(false); ui->dbGroupBox->setEnabled(false);
        ui->dbEditBtn->setText(tr("数据库编辑"));
    } else {
        m_dbEditStatus = MsgBox::question(this, tr("是否修改数据库配置信息?"));
        if(m_dbEditStatus) {
            ui->dbEnBox->setEnabled(true);
            ui->dbGroupBox->setEnabled(true);
            ui->dbEditBtn->setText(tr("保存配置"));
        }
    }
}



