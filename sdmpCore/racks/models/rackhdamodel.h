#ifndef RACKHDAMODEL_H
#define RACKHDAMODEL_H
#include "rackelemodel.h"

class APP_DLL_EXPORT RackHdaModel
{
public:
    uint id = 0;
    uint rack_id=0;
    double tg_apparent_power = 0;
    double a_apparent_power = 0;
    double b_apparent_power = 0;
    double tg_active_power = 0;
    double a_active_power = 0;
    double b_active_power = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    RackHdaModel(){}
    virtual ~RackHdaModel(){}
    static QString tableName() {return "rack_hda";}
};

QX_REGISTER_PRIMARY_KEY(RackHdaModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RackHdaModel, qx::trait::no_base_class_defined, 1)

#endif // RACKHDAMODEL_H
