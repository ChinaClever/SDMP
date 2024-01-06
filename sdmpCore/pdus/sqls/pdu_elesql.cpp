/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_elesql.h"

Pdu_EleSql::Pdu_EleSql()
{
    mIndexSql = Pdu_IndexSql::bulid();
    mNetJsonPack = Pdu_NetJsonPack::bulid();
}


Pdu_EleSql *Pdu_EleSql::bulid()
{
    static Pdu_EleSql* sington = nullptr;
    if(!sington) sington = new Pdu_EleSql();
    return sington;
}


void Pdu_EleSql::appendObject(const QJsonObject &obj)
{
    if(obj.isEmpty()) return;
    appnedArray(obj, "ele");
}

void Pdu_EleSql::appendTgObj(const QJsonObject &obj)
{
    mItem.id = 0; mItem.value = getData(obj, "ele"); append();
}

void Pdu_EleSql::appnedArray(const QJsonObject &json, const QString &key)
{
    QJsonArray jsonArray = getArray(json, key);
    for(int i=0; i<jsonArray.size(); ++i) {
        double v = jsonArray.at(i).toDouble();
        mItem.id = i+1; mItem.value = v; append();
    }
}

void Pdu_EleSql::eleWork()
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
        }
    } if(keys.size()) insert();
}

void Pdu_EleSql::append()
{
    ModelPtr it(addModel());
    it->pdu_id = mItem.pdu_id;
    it->type = mItem.type;
    it->indexes = mItem.id;
    it->value = mItem.value;
    mLstIts.append(it);
}

