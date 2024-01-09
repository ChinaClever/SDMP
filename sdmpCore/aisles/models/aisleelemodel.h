#ifndef AISLEELEMODEL_H
#define AISLEELEMODEL_H
#include "aisleindexmodel.h"

class APP_DLL_EXPORT AisleEleModel
{
public:
    uint id = 0;
    uint aisle_id=0;
    double tg_ele = 0;
    double a_ele = 0;
    double b_ele = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();

    AisleEleModel(){}
    virtual ~AisleEleModel(){}
    static QString tableName() {return "aisle_ele";}
};

QX_REGISTER_PRIMARY_KEY(AisleEleModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleEleModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEELEMODEL_H
