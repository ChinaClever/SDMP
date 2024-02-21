#ifndef CABINDEXMODEL_H
#define CABINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT CabIndexModel
{
public:
    uint id = 0;
    QString name;
    uint room_id=0;
    uint aisle_id = 0;
    uchar pdu_box = 0;
    uchar is_delete = 0;
    uchar is_disabled = 0;
    double pow_capacity = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    QDateTime updatetime = QDateTime::currentDateTime();

    virtual ~CabIndexModel(){} CabIndexModel(){}
    static QString tableName() {return CfgCom::db_prefix()+"cab_index";}
};

QX_REGISTER_PRIMARY_KEY(CabIndexModel, uint)  // 定义主键的类型
QX_REGISTER_HPP_APP(CabIndexModel, qx::trait::no_base_class_defined, 1)

#endif // CABINDEXMODEL_H
