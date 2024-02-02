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
    mDbCore = DbCoreThread::build(this);
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


}

void MainWindow::navBarSlot(int id)
{
    ui->stackedWid->setCurrentIndex(id);
}
