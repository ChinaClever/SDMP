#ifndef PDULOGMODEL_H
#define PDULOGMODEL_H
#include "pdu_hdasql.h"

class PduLogModel
{
public:
    uint id = 0;
    uint pdu_id = 0;
    uchar alarm_event = 0;
    QString state_type, content;
    QDateTime createtime = QDateTime::currentDateTime();

    PduLogModel(){}
    virtual ~PduLogModel(){}
    static QString tableName() {return "pdu_log";}
};

QX_REGISTER_PRIMARY_KEY(PduLogModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduLogModel, qx::trait::no_base_class_defined, 1)

#endif // PDULOGMODEL_H
