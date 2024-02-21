#ifndef GUI_RESTWID_H
#define GUI_RESTWID_H

#include "gui_mqttwid.h"

namespace Ui {
class Gui_RestWid;
}

class Gui_RestWid : public QWidget
{
    Q_OBJECT

public:
    explicit Gui_RestWid(QWidget *parent = nullptr);
    ~Gui_RestWid();

protected:
    void initPduTab();
    void initWidget();
    void initRoomTab();
    void initAisleTab();
    void initCabinetTab();
    void initRackTab();



    void saveHttpsCfg();
    void saveHttpCfg();
    void initHttpStatus();
    void saveCfg(sCfgRestUnit *it);
    void updateStatus(int status, QLabel *lab);
    void initColumnWidth(ComTableWid *tab);
    void setTableRow(ComTableWid *tab, int row, const QString &name,
                     const QString &api, const QString &param);

protected slots:
    void initFunSlot();

private slots:
    void on_httpEditBtn_clicked();
    void on_httpsEditBtn_clicked();
    void on_httpAclBox_currentIndexChanged(int index);
    void on_httpsAclBox_currentIndexChanged(int index);

private:
    Ui::Gui_RestWid *ui;
    ComTableWid *mPduTab;
    bool m_httpEditStatus = false;
    bool m_httpsEditStatus = false;
};

#endif // GUI_RESTWID_H
