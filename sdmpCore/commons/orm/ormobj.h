#ifndef ORMOBJ_H
#define ORMOBJ_H
/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */

#include "ormdb.h"
#include <QtConcurrent>

template<typename T>
class OrmObj : public OrmDb
{
public:
    explicit OrmObj() {init_cnt_max(); if(!isTableExists()) createTable(); }

    //qx::QxSqlQuery query("WHERE User.name = 'test 8'");
    long count(const qx::QxSqlQuery & query = qx::QxSqlQuery()) {return  qx::dao::count<T>(query, &sDb);}

    bool fetch_all(const QStringList & columns = QStringList()) {
        mListModel.clear(); bool ret = isOpen();
        if(ret) throwError(qx::dao::fetch_all(mListModel, &sDb, columns));
        return ret;
    }

    bool fetch_all(QList<T> &list, const QStringList & columns = QStringList()) {
        return throwError(qx::dao::fetch_all(list, &sDb, columns));
    }

    T *addModel() {return new T();}
    void ansyInsert(){QtConcurrent::run([&](){insert();});}
    bool insert(T &t) { return throwError(qx::dao::insert(t, &sDb));}
    bool insert(QList<T> &t) {return throwError(qx::dao::insert(t, &sDb));}
    int insert() {int cnt =0; bool ret=isOpen(); if(ret){update_cnt_max(); cnt=mLstIts.size();
            throwError(qx::dao::insert(mLstIts, &sDb, true));} mLstIts.clear(); return cnt;}
    //qx::QxSession session(sDb); session.insert(mLstIts); if(session.isValid()) mLstIts.clear();

    void save(QList<T> &t) {if(throwError(qx::dao::save(t, &sDb))) updateListModel(t);}
    void save(T &t) {if(throwError(qx::dao::save(t, &sDb))) updateListModel(t);}
    bool save() {bool ret=isOpen(); if(ret)ret=throwError(qx::dao::save(mListModel, &sDb)); return ret;}
    void ansySave(){QtConcurrent::run([&](){save();});}

    void updateListModel(T &t) {mListModel.removeByKey(t.id); mListModel.insert(t.id, t);}
    void updateListModel(QList<T> &t) {for (auto it : t) updateListModel(it);}

    // qx::QxSqlQuery query("WHERE User.name = 'test 8'");
    bool delete_by_query(const qx::QxSqlQuery & query) { return throwError(qx::dao::delete_by_query<T>(query, &sDb));}
    bool delete_by_id(T &t) {mListModel.removeByKey(t.id); return throwError(qx::dao::delete_by_id(t, &sDb));}

    QString tableName() {return T::tableName();}
    bool exist(T &t) {return qx::dao::exist(t, &sDb);}
    bool delete_all() { mListModel.clear(); return throwError(qx::dao::delete_all<T>(&sDb));}
    bool createTable() { return throwError(qx::dao::create_table<T>(&sDb));} //为默认数据库创建表格
    bool is_modified() {bool res=true; QDateTime dt=sql_updateTime(); if(dt>m_max_uptime)m_max_uptime=dt;else res=false; return res;}
    bool syncFun() { bool ret = is_modified(); if(ret){fetch_all();} return ret;}
    void update_cnt_max() {m_max_id += mLstIts.size(); m_cnt += mLstIts.size();}
    void init_cnt_max() {if(isOpen()){m_cnt=count(); m_max_id = sql_maxId();}}    

protected:
    typedef QSharedPointer<T> ModelPtr;
    qx::QxCollection<uint, T> mListModel;
    QList<ModelPtr> mLstIts;
    QDateTime m_max_uptime;
};


class OrmEleModelBase
{
public:
    quint64 id = 0;
    double tg_ele = 0;
    double a_ele = 0;
    double b_ele = 0;
    QDate createdate = QDate::currentDate();
    QTime createtime = QTime::currentTime();
    virtual ~OrmEleModelBase(){}
    OrmEleModelBase(){}
};


class OrmHdaModelBase
{
public:
    quint64 id = 0;
    double tg_apparent_power = 0;
    double a_apparent_power = 0;
    double b_apparent_power = 0;
    double tg_active_power = 0;
    double a_active_power = 0;
    double b_active_power = 0;
    QDateTime createtime = QDateTime::currentDateTime();
    virtual ~OrmHdaModelBase(){}
    OrmHdaModelBase(){}
};


#endif // ORMOBJ_H
