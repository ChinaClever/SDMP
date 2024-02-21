#ifndef RACKINDEXMODEL_H
#define RACKINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT RackIndexModel
{
public:
    uint id = 0;
    QString name;
    uint cabinet_id=0;
    uchar is_delete = 0;
    uchar a_port = 0;
    uchar b_port = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~RackIndexModel(){} RackIndexModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"rack_index";}
};

QX_REGISTER_PRIMARY_KEY(RackIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(RackIndexModel, qx::trait::no_base_class_defined, 1)

#endif // RACKINDEXMODEL_H
