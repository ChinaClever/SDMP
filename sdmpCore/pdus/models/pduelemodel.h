#ifndef PDUELEMODEL_H
#define PDUELEMODEL_H
#include "pduindexsql.h"

class APP_DLL_EXPORT PduEleModel
{
public:
    uint id = 0;
    uint pdu_id = 0;
    uchar type = 0;
    uchar indexes = 0;
    double value = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();

    PduEleModel(){}
    virtual ~PduEleModel(){}
    static QString tableName() {return "pdu_ele";}
};

QX_REGISTER_PRIMARY_KEY(PduEleModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduEleModel, qx::trait::no_base_class_defined, 1)

#endif // PDUELEMODEL_H
