#ifndef AISLEHDAMODEL_H
#define AISLEHDAMODEL_H
#include "aisleelemodel.h"

class APP_DLL_EXPORT AisleHdaModel
{
public:
    uint id = 0;
    uint aisle_id=0;
    double tg_apparent_power = 0;
    double a_apparent_power = 0;
    double b_apparent_power = 0;
    double tg_active_power = 0;
    double a_active_power = 0;
    double b_active_power = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    AisleHdaModel(){}
    virtual ~AisleHdaModel(){}
    static QString tableName() {return "aisle_hda";}
};

QX_REGISTER_PRIMARY_KEY(AisleHdaModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleHdaModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEHDAMODEL_H
