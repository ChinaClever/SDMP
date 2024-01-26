#ifndef GUI_DBWID_H
#define GUI_DBWID_H

#include <QWidget>
#include "backcolourcom.h"

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
    Ui::Gui_DbWid *ui;
};

#endif // GUI_DBWID_H
