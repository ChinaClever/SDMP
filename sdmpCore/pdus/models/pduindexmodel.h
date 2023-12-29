#ifndef PDUINDEXMODEL_H
#define PDUINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT PduIndexModel
{
public:
    uint id = 0;
    QString uid, ip;
    uchar cascade_num = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    PduIndexModel(){}
    virtual ~PduIndexModel(){}
    static QString tableName() {return "pdu_index";}
};

QX_REGISTER_PRIMARY_KEY(PduIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(PduIndexModel, qx::trait::no_base_class_defined, 1)

#endif // PDUINDEXMODEL_H
