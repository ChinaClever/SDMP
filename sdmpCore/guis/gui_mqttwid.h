#ifndef GUI_MQTTWID_H
#define GUI_MQTTWID_H

#include "dbthreadcore.h"
#include "backcolourcom.h"
#include "comtablewid.h"
#include "msgbox.h"
#include "cfgcom.h"
#include <QDialog>

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
    Ui::Gui_MqttWid *ui;
};

#endif // GUI_MQTTWID_H
