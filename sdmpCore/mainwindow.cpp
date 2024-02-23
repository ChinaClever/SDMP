/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDbCore = DbThreadCore::build(this);
    mNavBarWid = new NavBarWid(ui->barWid);
    QTimer::singleShot(50,this,SLOT(initFunSlot())); //延时初始化
    connect(mNavBarWid, SIGNAL(navBarSig(int)), this, SLOT(navBarSlot(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFunSlot()
{
    initWid();
}

void MainWindow::initWid()
{
    mMainWid = new Gui_MainWid(this);
    ui->stackedWid->addWidget(mMainWid);

    mDbWid = new Gui_DbWid(this);
    ui->stackedWid->addWidget(mDbWid);

    mRestWid = new Gui_RestWid(this);
    ui->stackedWid->addWidget(mRestWid);

    mMqttWid = new Gui_MqttWid(this);
    ui->stackedWid->addWidget(mMqttWid);
}

void MainWindow::navBarSlot(int id)
{
    ui->stackedWid->setCurrentIndex(id);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(MsgBox::information(this, tr("关闭软件，需要再次确认"))) {
        QMainWindow::closeEvent(event);
        QCoreApplication::quit();
        QCoreApplication::exit(0);
        QApplication::quit();
    }
}
