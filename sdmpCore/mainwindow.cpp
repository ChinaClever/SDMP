/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cabinets/network/cab_httpserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Cab_HttpServer *obj = new Cab_HttpServer(this);
    obj->http_listen(43796);
    mDbCore = new DbCoreThread(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
