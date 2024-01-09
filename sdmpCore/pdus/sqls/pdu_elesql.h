#ifndef PDU_ELESQL_H
#define PDU_ELESQL_H
#include "pdu_indexsql.h"

enum DType{Tg, Line, Loop, Output, Group, Dual, Env=6, Sensor, CabTg=11, CabLine, CabLoop};
enum DTopic{Relay, Vol, Cur, Pow, ArtPow, ReactivePow, Ele, PF, HdaEle, LineVol, Tem=11, Hum, Door1=21, Door2, Water, Smoke, Wind};

struct sPduEleItem
{
    uint pdu_id;
    uchar type; // 1 相数据  2 回路数据 ３　输出位数据 4组数据 6 环境 7 传感器
    uchar id; // 0 表示统一设置
    double value;
};

class Pdu_EleSql: public OrmObj<PduEleModel>
{
    Pdu_EleSql();
public:
    static Pdu_EleSql *build();
    void eleWork();

private:
    void append();
    void appendTgObj(const QJsonObject &obj);
    void appendObject(const QJsonObject &obj);
    void appnedArray(const QJsonObject &json, const QString &key);

private:
    sPduEleItem mItem;
    Pdu_IndexSql *mIndexSql=nullptr;
    Pdu_NetJsonPack *mNetJsonPack=nullptr;
};

#endif // PDU_ELESQL_H
