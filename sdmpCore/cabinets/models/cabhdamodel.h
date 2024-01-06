#ifndef CABHDAMODEL_H
#define CABHDAMODEL_H
#include "cabelemodel.h"

class APP_DLL_EXPORT CabHdaModel
{
public:
    uint id = 0;
    uint cabinet_id=0;
    double tg_apparent_power = 0;
    double a_apparent_power = 0;
    double b_apparent_power = 0;
    double tg_active_power = 0;
    double a_active_power = 0;
    double b_active_power = 0;
    QDateTime createtime = QDateTime::currentDateTime();

    CabHdaModel(){}
    virtual ~CabHdaModel(){}
    static QString tableName() {return "cab_hda";}
};

QX_REGISTER_PRIMARY_KEY(CabHdaModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabHdaModel, qx::trait::no_base_class_defined, 1)

#endif // CABHDAMODEL_H
