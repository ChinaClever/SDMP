#ifndef CABELEMODEL_H
#define CABELEMODEL_H
#include "cab_hdasql.h"

class APP_DLL_EXPORT CabEleModel
{
public:
    uint id = 0;
    uint cabinet_id=0;
    double tg_ele = 0;
    double a_ele = 0;
    double b_ele = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();

    CabEleModel(){}
    virtual ~CabEleModel(){}
    static QString tableName() {return "cab_ele";}
};

QX_REGISTER_PRIMARY_KEY(CabEleModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabEleModel, qx::trait::no_base_class_defined, 1)

#endif // CABELEMODEL_H
