#ifndef GUI_REDISDLG_H
#define GUI_REDISDLG_H

#include "dbthreadcore.h"
#include "backcolourcom.h"
#include "comtablewid.h"
#include "msgbox.h"
#include "cfgcom.h"
#include <QDialog>

namespace Ui {
class Gui_RedisDlg;
}

class Gui_RedisDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Gui_RedisDlg(QWidget *parent = nullptr);
    ~Gui_RedisDlg();
    void init(int id);

protected:
    void setTitle(int id);
    void getUnit(int id);

private slots:
    void onAccepted();

private:
    Ui::Gui_RedisDlg *ui;
    sCfgRedisUnit *m_unit=nullptr;
};

#endif // GUI_REDISDLG_H
