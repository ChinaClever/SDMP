/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "pdu_indexsql.h"

Pdu_IndexSql::Pdu_IndexSql()
{
    mNetJsonPack = Pdu_NetJsonPack::bulid();
    //test();
}



Pdu_IndexSql *Pdu_IndexSql::bulid()
{
    static Pdu_IndexSql* sington = nullptr;
    if(!sington)  sington = new Pdu_IndexSql();
    return sington;
}


void Pdu_IndexSql::toNetPack()
{
    foreach (const auto &it, mListModel) {
        auto obj = it.second; uint key = it.first; mKeyHash.insert(obj.uid, key);
        if(!obj.is_delete) mNetJsonPack->append(obj.uid, obj.ip, obj.cascade_num);
        else mDeleteHash.insert(obj.uid, obj);
    }
}

void Pdu_IndexSql::syncNetPack()
{
    QList<PduIndexModel> modelLst;
    QStringList onLst = mNetJsonPack->online_list();
    foreach (const auto &uid, onLst) {
        if(!mKeyHash.contains(uid)) {
            PduIndexModel it; it.uid = uid; it.is_delete = 0;
            bool ret = mNetJsonPack->getByKey(uid, it.ip, it.cascade_num);
            if(ret) modelLst.append(it);
        } else if(mDeleteHash.contains(uid)){
            PduIndexModel it = mDeleteHash.value(uid);
            mDeleteHash.remove(uid); it.is_delete = 0;
            modelLst.append(it);
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
    mNetJsonPack = Pdu_NetJsonPack::bulid();
    fetch_all(); mKeyHash.clear(); toNetPack(); //syncNetPack();
}

uint Pdu_IndexSql::getId(const QString &key)
{
    uint ret = 0;
    if(mKeyHash.contains(key)) {
        ret = mKeyHash.value(key);
    }
    return ret;
}

QStringList Pdu_IndexSql::getkeys()
{
    return mNetJsonPack->online_list();
}


void Pdu_IndexSql::test()
{
    initFun();
    QtConcurrent::run([&](){
        while(1) {
            QThread::sleep(1);
            syncNetPack();

            cout << mNetJsonPack->offline_list();
        }
    });


    return ;


    QList<PduIndexModel> itLst;
    for(int i = 0;i < 5;i ++) {
        PduIndexModel it;
        it.uid = QString ("lzy %1").arg(i);
        it.ip = "123456";
        it.cascade_num = 0;
        itLst.append(it);
    }
    cout << delete_all() << count() << mListModel.size();
    cout; save(itLst); cout; save(itLst);
    qDebug()  << count() <<  fetch_all() << mListModel.size() ;
}
