#ifndef GUI_MAINWID_H
#define GUI_MAINWID_H

#include <QWidget>
#include "gui_dbwid.h"

namespace Ui {
class Gui_MainWid;
}

class Gui_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit Gui_MainWid(QWidget *parent = nullptr);
    ~Gui_MainWid();

private:
    void pduNum();
    void idcCnt();
    void netCnt();
    void secsUpdate();
    void convertSeconds(uint seconds, int& days, int& hours, int& minutes);


private slots:
    void timeoutDone();

private:
    Ui::Gui_MainWid *ui;
    QTimer *timer=nullptr;
};

#endif // GUI_MAINWID_H
