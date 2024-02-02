#ifndef GUI_DBWID_H
#define GUI_DBWID_H

#include "gui_dbsetdlg.h"

namespace Ui {
class Gui_DbWid;
}

class Gui_DbWid : public QWidget
{
    Q_OBJECT

public:
    explicit Gui_DbWid(QWidget *parent = nullptr);
    ~Gui_DbWid();

private:
    void saveCfg();
    void initCfg();
    void updateDbCnt();
    void initCntTable();
    void initSetTable();
    void updateSetTable();
    void updateStatus(int status);
    void setTextColor(bool pass);
    void setTableItem(int id, int column, quint64 number);

private slots:
    void timeoutDone();
    void initFunSlot();
    void itemDoubleSlot(int row);
    void on_dbEditBtn_clicked();
    void insertTextSlot(const QString &msg, bool pass);

private:
    Ui::Gui_DbWid *ui;
    QTimer *timer=nullptr;
    ComTableWid *mCntTableWid;
    ComTableWid *mSetTableWid;
    bool m_dbEditStatus=false;
    uint mId = 0;
};

#endif // GUI_DBWID_H
