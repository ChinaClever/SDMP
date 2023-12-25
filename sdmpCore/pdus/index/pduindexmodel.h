#ifndef PDUINDEXMODEL_H
#define PDUINDEXMODEL_H
#include "ormobj.h"

class APP_DLL_EXPORT PduIndexModel
{
public:
    uint id;
    QString name;
    int age;

    PduIndexModel(): id(0){} //初始化id为1
    virtual ~PduIndexModel(){}
    static QString tableName() {return "pdu_user";}
};

QX_REGISTER_PRIMARY_KEY(PduIndexModel, uint)  // 定义主键的类型

/************************************************************
 * QX_REGISTER_HPP_APP 宏是必须的，用于将 User 类注册到 QxOrm 的上下文中
 * 参数一：表示要注册的当前类 - User
 * 参数二：基类，如果没有基类，则使用 qx::trait::no_base_class_defined
 * 参数三：用于序列化的类版本
 * ***********************************************************/
QX_REGISTER_HPP_APP(PduIndexModel, qx::trait::no_base_class_defined, 1)

#endif // PDUINDEXMODEL_H
