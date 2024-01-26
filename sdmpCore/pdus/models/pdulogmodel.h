#ifndef PDULOGMODEL_H
#define PDULOGMODEL_H
#include "pduhdamodel.h"

class APP_DLL_EXPORT PduLogModel
{
public:
    uint id = 0;
    uint pdu_id = 0;
    uchar alarm_event = 0;
    QString state_type, content;
    QDateTime createtime = QDateTime::currentDateTime();

    virtual ~PduLogModel(){} PduLogModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"pdu_log";}
};

QX_REGISTER_PRIMARY_KEY(PduLogModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduLogModel, qx::trait::no_base_class_defined, 1)

#endif // PDULOGMODEL_H
