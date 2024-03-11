#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbthreadcore.h"
#include "navbarwid.h"
#include "gui_mainwid.h"
#include "commons/QtRedis/redisobj.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void initWid();

protected slots:
    void initFunSlot();
    void navBarSlot(int);
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;
    DbThreadCore *mDbCore;    
    NavBarWid *mNavBarWid;
    Gui_MainWid *mMainWid;
    Gui_RestWid *mRestWid;
    Gui_MqttWid *mMqttWid;
    Gui_RedisWid *mRedisWid;
    Gui_DbWid *mDbWid;
};
#endif // MAINWINDOW_H
