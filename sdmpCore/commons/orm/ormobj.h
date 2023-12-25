#ifndef ORMOBJ_H
#define ORMOBJ_H
/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */

#include "ormdb.h"

template<typename T>
class OrmObj : public OrmDb
{
public:
    explicit OrmObj() {
        if(!isTableExists()) createTable();
    }

    //qx::QxSqlQuery query("WHERE User.name = 'test 8'");
    int count(const qx::QxSqlQuery & query = qx::QxSqlQuery()) {return  qx::dao::count<T>(query, &mDb);}

    bool fetch_all(const QStringList & columns = QStringList()) {
        mListModel.clear(); return throwError(qx::dao::fetch_all(mListModel, &mDb, columns));
    }

    bool fetch_all(QList<T> &list, const QStringList & columns = QStringList()) {
        return throwError(qx::dao::fetch_all(list, &mDb, columns));
    }

    bool insert() {return throwError(qx::dao::insert(mListModel, &mDb));}
    bool insert(T &t) {return throwError(qx::dao::insert(t, &mDb));}
    bool insert(QList<T> &t) {return throwError(qx::dao::insert(t, &mDb));}

    bool save() {return throwError(qx::dao::save(mListModel, &mDb));}
    bool save(T &t) {return throwError(qx::dao::save(t, &mDb));}
    bool save(QList<T> &t) {return throwError(qx::dao::save(t, &mDb));}

    // qx::QxSqlQuery query("WHERE User.name = 'test 8'");
    bool delete_by_query(const qx::QxSqlQuery & query) { return throwError(qx::dao::delete_by_query<T>(query, &mDb));}
    bool delete_by_id(T &t) {return throwError(qx::dao::delete_by_id(t, &mDb));}

    QString tableName() {return T::tableName();}
    bool exist(T &t) {return qx::dao::exist(t, &mDb);}
    bool delete_all() {return throwError(qx::dao::delete_all<T>(&mDb));}
    bool createTable() {return throwError(qx::dao::create_table<T>(&mDb));} //为默认数据库创建表格

protected:
     QList<T> mListModel;
};

#endif // ORMOBJ_H
