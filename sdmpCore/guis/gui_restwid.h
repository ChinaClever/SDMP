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
    void initColumnWidth(ComTableWid *tab);
    void setTableRow(ComTableWid *tab, int row, const QString &name, const QString &api, const QString &param);
    void initPduTab();
    void initWidget();
    void saveCfg();

protected slots:
    void initFunSlot();
    //void itemDoubleSlot(int);

private slots:
    void on_httpEditBtn_clicked();

private:
    Ui::Gui_RestWid *ui;
    ComTableWid *mPduTab;
    bool m_httpEditStatus = false;
};

#endif // GUI_RESTWID_H
