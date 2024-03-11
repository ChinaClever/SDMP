#ifndef GUI_REDISWID_H
#define GUI_REDISWID_H

#include "gui_redisdlg.h"

namespace Ui {
class Gui_RedisWid;
}

class Gui_RedisWid : public QWidget
{
    Q_OBJECT
public:
    explicit Gui_RedisWid(QWidget *parent = nullptr);
    ~Gui_RedisWid();

private:
    void initCfg();
    void saveCfg();
    void initSetTable();
    void updateSetTable();
    void updateStatus();

private slots:
    void timeoutDone();
    void initFunSlot();
    void itemDoubleSlot(int row);

    void on_redisEditBtn_clicked();

private:
    Ui::Gui_RedisWid *ui;
    QTimer *timer=nullptr;
    ComTableWid *mSetTableWid;
    bool m_dbEditStatus=false;
};

#endif // GUI_REDISWID_H
