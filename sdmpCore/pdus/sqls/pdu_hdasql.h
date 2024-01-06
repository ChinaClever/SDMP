#ifndef PDU_HDASQL_H
#define PDU_HDASQL_H
#include "pdu_elesql.h"



struct sPduHdaItem
{
    uint pdu_id; //
    uchar type; // 1 相数据  2 回路数据 ３　输出位数据 4组数据 6 环境 7 传感器
    uchar topic; // 0 开关  1 电压  2 电流  3 功率  11温度 12湿度
    uchar id; // 0 表示统一设置
    double value;
};


class Pdu_HdaSql : public OrmObj<PduHdaModel>
{
    Pdu_HdaSql();
public:
    static Pdu_HdaSql *bulid();
    void hdaWork();

private:
    void append();
    void envData(const QJsonObject &obj);
    void appendTgObj(const QJsonObject &obj);
    void appendObject(const QJsonObject &obj);
    void appnedArray(const QJsonObject &json, const QString &key);

private:
    sPduHdaItem mItem;
    Pdu_IndexSql *mIndexSql=nullptr;
    Pdu_NetJsonPack *mNetJsonPack=nullptr;
};

#endif // PDU_HDASQL_H
