/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_hdasql.h"

Pdu_HdaSql::Pdu_HdaSql()
{
    mIndexSql = Pdu_IndexSql::build();
    mNetJsonPack = Pdu_NetJsonPack::build();
    // test();
}

Pdu_HdaSql *Pdu_HdaSql::build()
{
    static Pdu_HdaSql* sington = nullptr;
    if(!sington) sington = new Pdu_HdaSql();
    return sington;
}

void Pdu_HdaSql::appendTgObj(const QJsonObject &obj)
{
    mItem.id = 0; mItem.topic = DTopic::Pow; mItem.value = getData(obj, "pow"); append();
    mItem.topic = DTopic::ArtPow; mItem.value = getData(obj, "apparent_pow");  append();
}

void Pdu_HdaSql::appendObject(const QJsonObject &obj)
{
    if(obj.isEmpty()) return;
    QString key = "vol_value";
    mItem.topic = DTopic::Vol;
    appnedArray(obj, key);

    key = "cur_value";
    mItem.topic = DTopic::Cur;
    appnedArray(obj, key);

    key = "pow_value";
    mItem.topic = DTopic::Pow;
    appnedArray(obj, key);

    key = "apparent_pow";
    mItem.topic = DTopic::ArtPow;
    appnedArray(obj, key);
}

void Pdu_HdaSql::envData(const QJsonObject &obj)
{
    if(obj.isEmpty()) return;
    QString key = "tem_value";
    mItem.topic = DTopic::Tem;
    appnedArray(obj, key);

    key = "hum_value";
    mItem.topic = DTopic::Hum;
    appnedArray(obj, key);
}

void Pdu_HdaSql::appnedArray(const QJsonObject &json, const QString &key)
{
    QJsonArray jsonArray = getArray(json, key);
    for(int i=0; i<jsonArray.size(); ++i) {
        double v = jsonArray.at(i).toDouble();
        mItem.id = i+1; mItem.value = v; append();
    }
}

int Pdu_HdaSql::workDown()
{
    QStringList keys = mIndexSql->getkeys();
    foreach (const auto &key, keys) {
        mItem.pdu_id = mIndexSql->getId(key); if(mItem.pdu_id) {
            QJsonObject obj, root = mNetJsonPack->dev(key).toObject();
            mItem.type = DType::Tg; obj = getObject(root, "pdu_tg_data"); appendTgObj(obj);
            mItem.type = DType::Line; obj = getObject(root, "line_item_list"); appendObject(obj);
            mItem.type = DType::Loop; obj = getObject(root, "loop_item_list"); appendObject(obj);
            mItem.type = DType::Output; obj = getObject(root, "output_item_list"); appendObject(obj);
            mItem.type = DType::Group; obj = getObject(root, "group_item_list"); appendObject(obj);
            mItem.type = DType::Env; obj = getObject(root, "env_item_list"); envData(obj);
        }
    }

    return insert();
}


void Pdu_HdaSql::append()
{
    ModelPtr it(addModel());
    it->pdu_id = mItem.pdu_id;
    it->type = mItem.type;
    it->topic = mItem.topic;
    it->indexes = mItem.id;
    it->value = mItem.value;
    mLstIts.append(it);
}
