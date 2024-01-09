/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_indexsql.h"

Pdu_IndexSql::Pdu_IndexSql()
{
    mNetJsonPack = Pdu_NetJsonPack::build();
}


Pdu_IndexSql *Pdu_IndexSql::build()
{
    static Pdu_IndexSql* sington = nullptr;
    if(!sington)  sington = new Pdu_IndexSql();
    return sington;
}


void Pdu_IndexSql::toNetPack()
{
    foreach (const auto &it, mListModel) {
        auto obj = it.second; uint key = it.first; mKeyHash.insert(obj.key, key);
        if(!obj.is_delete) mNetJsonPack->append(obj.key, obj.ip, obj.cascade_num);
        else mDeleteHash.insert(obj.key, obj);
    }
}

void Pdu_IndexSql::syncNetPack()
{
    QList<PduIndexModel> modelLst;
    QStringList onLst = mNetJsonPack->online_list();
    foreach (const auto &key, onLst) {
        if(!mKeyHash.contains(key)) {
            PduIndexModel it; it.key = key; it.is_delete = 0;
            bool ret = mNetJsonPack->getByKey(key, it.ip, it.cascade_num);
            it.id = getId(key); if(ret) modelLst.append(it);
        } else if(mDeleteHash.contains(key)){
            PduIndexModel it = mDeleteHash.value(key);
            mDeleteHash.remove(key); it.is_delete = 0;
            it.id = getId(key); modelLst.append(it);
        }
    } if(modelLst.size()) {save(modelLst); toNetPack();}
}

QString Pdu_IndexSql::getKey(const QString &ip, uchar addr)
{
    return mNetJsonPack->getKey(ip, addr);
}

uint Pdu_IndexSql::getId(const QString &ip, uchar addr)
{
    QString key = getKey(ip, addr);
    return getId(key);
}

void Pdu_IndexSql::initFun()
{
    mNetJsonPack = Pdu_NetJsonPack::build();
    fetch_all(); mKeyHash.clear(); toNetPack(); //syncNetPack();
}

uint Pdu_IndexSql::getId(const QString &key)
{
    uint ret = 0; if(mKeyHash.contains(key)) {
        ret = mKeyHash.value(key);
    }
    return ret;
}

QStringList Pdu_IndexSql::getkeys()
{
    return mNetJsonPack->online_list();
}

QString Pdu_IndexSql::getKey(uint id)
{
    QString res; if(mListModel.contains(id)) {
        res = mListModel.getByKey(id).key;
    }
    return res;
}

