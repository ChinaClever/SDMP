#ifndef RACKELEMODEL_H
#define RACKELEMODEL_H
#include "rackindexmodel.h"

class APP_DLL_EXPORT RackEleModel
{
public:
    uint id = 0;
    uint rack_id=0;
    double tg_ele = 0;
    double a_ele = 0;
    double b_ele = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();

    RackEleModel(){}
    virtual ~RackEleModel(){}
    static QString tableName() {return "rack_ele";}
};

QX_REGISTER_PRIMARY_KEY(RackEleModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RackEleModel, qx::trait::no_base_class_defined, 1)


#endif // RACKELEMODEL_H
