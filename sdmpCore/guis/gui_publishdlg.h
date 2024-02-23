#ifndef GUI_PUBLISHDLG_H
#define GUI_PUBLISHDLG_H

#include "dbthreadcore.h"
#include "backcolourcom.h"
#include "comtablewid.h"
#include "msgbox.h"
#include "cfgcom.h"
#include <QDialog>

namespace Ui {
class Gui_PublishDlg;
}

class Gui_PublishDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Gui_PublishDlg(QWidget *parent = nullptr);
    ~Gui_PublishDlg();
    void init(int id);

protected:
    void setTitle(int id);
    void getUnit(int id);

private slots:
    void onAccepted();

private:
    Ui::Gui_PublishDlg *ui;    
    sCfgMqttUnit *m_unit=nullptr;
};

#endif // GUI_PUBLISHDLG_H
