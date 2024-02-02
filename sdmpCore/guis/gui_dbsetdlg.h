#ifndef GUI_DBSETDLG_H
#define GUI_DBSETDLG_H

#include "dbcorethread.h"
#include "backcolourcom.h"
#include "comtablewid.h"
#include "msgbox.h"
#include "cfgcom.h"
#include <QDialog>

namespace Ui {
class Gui_DbSetDlg;
}

class Gui_DbSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Gui_DbSetDlg(QWidget *parent = nullptr);
    ~Gui_DbSetDlg();
    void init(int id);

protected:
    void setTitle(int id);
    void getSqlUnit(int id);

private slots:
    void onAccepted();

private:
    Ui::Gui_DbSetDlg *ui;
    sCfgSqlUnit *m_hda=nullptr;
    sCfgSqlUnit *m_ele=nullptr;
};

#endif // GUI_DBSETDLG_H
