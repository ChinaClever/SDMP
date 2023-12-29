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
    explicit OrmObj() { if(!isTableExists()) createTable(); }

    //qx::QxSqlQuery query("WHERE User.name = 'test 8'");
    int count(const qx::QxSqlQuery & query = qx::QxSqlQuery()) {return  qx::dao::count<T>(query, &sDb);}

    bool fetch_all(const QStringList & columns = QStringList()) {
        mListModel.clear(); return throwError(qx::dao::fetch_all(mListModel, &sDb, columns));
    }

    bool fetch_all(QList<T> &list, const QStringList & columns = QStringList()) {
        return throwError(qx::dao::fetch_all(list, &sDb, columns));
    }

    T *addModel() {return new T();}
    void ansyInsert(){QtConcurrent::run([&](){insert();});}
    bool insert(T &t) { return throwError(qx::dao::insert(t, &sDb));}
    bool insert(QList<T> &t) {return throwError(qx::dao::insert(t, &sDb));}
    void insert() {if(throwError(qx::dao::insert(mLstIts, &sDb))) mLstIts.clear();}

    void save(QList<T> &t) {if(throwError(qx::dao::save(t, &sDb))) updateListModel(t);}
    void save(T &t) {if(throwError(qx::dao::save(t, &sDb))) updateListModel(t);}
    bool save() { return throwError(qx::dao::save(mListModel, &sDb));}
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

protected:
    typedef QSharedPointer<T> ModelPtr;
    qx::QxCollection<uint, T> mListModel;
    QList<ModelPtr> mLstIts;
};

#endif // ORMOBJ_H
