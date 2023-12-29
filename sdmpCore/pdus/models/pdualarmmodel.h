#ifndef PDUALARMMODEL_H
#define PDUALARMMODEL_H
#include "pduhdasql.h"

class PduAlarmModel
{
public:
    uint id = 0;
    uint pdu_id = 0;
    QString status, content;
    QDateTime createtime = QDateTime::currentDateTime();

    PduAlarmModel(){}
    virtual ~PduAlarmModel(){}
    static QString tableName() {return "pdu_alarm";}
};

QX_REGISTER_PRIMARY_KEY(PduAlarmModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduAlarmModel, qx::trait::no_base_class_defined, 1)

#endif // PDUALARMMODEL_H
