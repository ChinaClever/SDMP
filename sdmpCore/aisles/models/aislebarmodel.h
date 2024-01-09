#ifndef AISLEBARMODEL_H
#define AISLEBARMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT AisleBarModel
{
public:
    uint id = 0;
    uint aisle_id=0;
    uchar a_bar_id = 0;
    uchar b_bar_id = 0;
    QString a_bar_ip, b_bar_ip;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    AisleBarModel(){}
    virtual ~AisleBarModel(){}
    static QString tableName() {return "aisle_bar";}
};

QX_REGISTER_PRIMARY_KEY(AisleBarModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(AisleBarModel, qx::trait::no_base_class_defined, 1)

#endif // AISLEBARMODEL_H
