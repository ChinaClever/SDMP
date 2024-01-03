#ifndef PDUEVENTMODEL_H
#define PDUEVENTMODEL_H
#include "pdu_alarmsql.h"

class PduEventModel
{
public:
    uint id = 0;
    uint pdu_id = 0;
    QString type, content;
    QDateTime createtime = QDateTime::currentDateTime();

    PduEventModel(){}
    virtual ~PduEventModel(){}
    static QString tableName() {return "pdu_event";}
};

QX_REGISTER_PRIMARY_KEY(PduEventModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduEventModel, qx::trait::no_base_class_defined, 1)

#endif // PDUEVENTMODEL_H
