#ifndef GUI_MQTTWID_H
#define GUI_MQTTWID_H
#include "gui_publishdlg.h"

namespace Ui {
class Gui_MqttWid;
}

class Gui_MqttWid : public QWidget
{
    Q_OBJECT

public:
    explicit Gui_MqttWid(QWidget *parent = nullptr);
    ~Gui_MqttWid();

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
    void on_mqttEditBtn_clicked();
    void on_dbEnBox_currentIndexChanged(int index);

private:
    Ui::Gui_MqttWid *ui;
    QTimer *timer=nullptr;
    ComTableWid *mSetTableWid;
    bool m_dbEditStatus=false;
};

#endif // GUI_MQTTWID_H
