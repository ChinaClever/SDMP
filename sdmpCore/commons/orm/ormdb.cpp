/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */

#include "ormdb.h"
#include <QThreadPool>

// QMutex OrmDb::msLock;
QSqlDatabase OrmDb::sDb;
OrmDb::OrmDb()
{
    initDb();
}

//非阻塞方式延时,现在很多人推荐的方法
void OrmDb::mdelay(int msec)
{
    QEventLoop loop;
    msec += QRandomGenerator::global()->bounded(msec);
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

bool OrmDb::isTableExists()
{
    QSqlQuery query(sDb);
    query.prepare("SHOW TABLES LIKE :table");
    query.bindValue(":table", tableName()); // 将参数绑定到查询中
    if (!query.exec())  return false; // 执行查询失败，处理错误
    return query.next(); // 如果查询结果中有数据行，则表示表存在
}

/**
 * @brief 删除
 * @param condition
 */
bool OrmDb::sql_remove(const QString &condition)
{
    QString sql = "DELETE FROM %1 WHERE %2";
    bool ret = sqlQuery(sql.arg(tableName(), condition));
    //if(ret) {sql = "VACUUM "; ret = sqlQuery(sql);}
    return ret;
}

bool OrmDb::sql_remove(const QString &name, const QString &vale)
{
    QString sql = "%1 = \'%2\'";
    return sql_remove(sql.arg(name, vale));
}

bool OrmDb::sql_remove(int id)
{
    return sql_remove(QString("id = %1").arg(id));
}

bool OrmDb::sql_removeMinIds(int id)
{
    return sql_remove(QString("id < %1").arg(id));
}

bool OrmDb::sql_removeMaxIds(int id)
{
    return sql_remove(QString("id > %1").arg(id));
}


quint64 OrmDb::sql_id_select(const QString &sql)
{
    int id = 0; QSqlQuery query(sDb);
    if(sqlQuery(query, sql)) {
        if(query.next()) id = query.value(0).toULongLong();
    }
    return id;
}

quint64 OrmDb::sql_maxId(const QString &column_name, const QString &condition)
{
    QString sql = "select max(%1) from %2 %3";
    return sql_id_select(sql.arg(column_name, tableName(), condition));
}

quint64 OrmDb::sql_maxId()
{
    return sql_maxId("id", "");
}

quint64 OrmDb::sql_maxId(const QString &condition)
{
    return sql_maxId("id", QString("where %1").arg(condition));
}

int OrmDb::sql_minId(const QString &column_name, const QString &condition)
{
    QString sql = "select MIN(%1) from %2 %3";
    return sql_id_select(sql.arg(column_name, tableName(), condition));
}

int OrmDb::sql_minId(const QString &condition)
{
    return sql_minId("id", QString("where %1").arg(condition));
}

int OrmDb::sql_minId()
{
    return sql_minId("id", "");
}


/**
 * @brief 函数返回指定列的值的数目
 * @param column_name
 * @return
 */
int OrmDb::sql_counts(const QString &column_name, const QString &condition)
{
    QString sql = "select count(DISTINCT %1) from %2 %3";
    return sql_id_select(sql.arg(column_name, tableName(), condition));
}

int OrmDb::sql_counts(const QString &name)
{
    return sql_counts(name, "");
}

int OrmDb::sql_counts()
{
    return sql_counts("id");
}

int OrmDb::sql_contains(const QString &name, const QString &value)
{
    QString condition = QString("where %1=\'%2\'").arg(name, value);
    return sql_counts(name, condition);
}

/**
 * @brief 数据库最多保存多少条数据，删除掉其它的
 * @param count
 * @return
 */
bool OrmDb::sql_countsRemove(int count)
{
    bool ret = false;
    int rtn = sql_counts(); if(rtn > count) {
        int id = sql_minId() + (rtn-count);
        ret = sql_removeMinIds(id);
    }

    return ret;
}


QDateTime OrmDb::sql_updateTime()
{
    QString query = "SELECT MAX(%1) AS maxModificationTime FROM %2 LIMIT 1";
    QDateTime dt(QDate(2024,1,1), QTime(0,0,0)); QSqlQuery sqlQuery(query.arg("update_time", tableName()));  // 执行查询语句
    if (sqlQuery.exec() && sqlQuery.next()) dt = sqlQuery.value("maxModificationTime").toDateTime();
    return dt;
}

/**
 * @brief 函数返回列的所有值
 * @param column_name 列名
 * @param condition 条件
 * @return
 */
QVariantList OrmDb::sql_listColumn(const QString &column_name, const QString &condition)
{
    QVariantList list; QSqlQuery query(sDb);
    QString sql = QString("select DISTINCT %1 from %2 %3")
                      .arg(column_name, tableName(), condition);
    if(sqlQuery(query, sql)) {
        while(query.next()) list << query.value(0);
    }

    return list;
}

QVariantList OrmDb::sql_selectIds(const QString &condition)
{
    return sql_listColumn("id", condition);
}

bool OrmDb::sql_updateColumn(const QString& column_name, double value, const QString &condition)
{
    QString sql = QString("update %1 set %2=%3 %4")
                      .arg(tableName(), column_name).arg(value).arg(condition);
    return sqlQuery(sql);
}

bool OrmDb::sql_updateColumn(const QString& column_name, QString value, const QString &condition)
{
    QString sql = QString("update  %1 set %2=\'%3\' where %4")
                      .arg(tableName(), column_name, value, condition);
    return sqlQuery(sql);
}

bool OrmDb::sql_clear()
{
    QString sql = "TRUNCATE TABLE %1";
    sqlQuery(sql.arg(tableName()));

    sql = "delete from %1";
    sqlQuery(sql.arg(tableName()));
    return sqlQuery("VACUUM");
}



// 获取系统支持的数据库驱动程序列表
bool OrmDb::availableDrivers()
{
    // 检查系统是否支持 MySQL 驱动程序
    bool ret = QSqlDatabase::isDriverAvailable("QMYSQL");
    qDebug() <<  QSqlDatabase::drivers();if (ret) {
        qDebug() << "MySQL driver is available.";
    } else {
        qDebug() << "MySQL driver is not available.";
    }
    return ret;
}

void OrmDb::initDebugInfo()
{
    qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(false);
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(false);
    qx::QxSqlDatabase::getSingleton()->setTraceSqlQuery(false);
    qx::QxSqlDatabase::getSingleton()->setTraceSqlBoundValuesOnError(false);
    qx::QxSqlDatabase::getSingleton()->setTraceSqlRecord(false);
    qx::QxSqlDatabase::getSingleton()->setTraceSqlBoundValues(false);
    qx::QxSqlDatabase::getSingleton()->setTraceSqlBoundValuesOnError(false);
    int cnt = QThreadPool::globalInstance()->maxThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(15*cnt);
}



void OrmDb::initDb()
{
    if(!sDb.isOpen()) { CfgCom::build();
        sCfgDbItem *it = &CfgCom::mCfgDb;
        sDb = QSqlDatabase::addDatabase("QMYSQL");
        sDb.setDatabaseName(it->name);
        sDb.setHostName(it->host);
        sDb.setUserName(it->user);
        sDb.setPassword(it->pwd);
        if(sDb.open()) initDebugInfo();
        else qCritical() << "DB open error";
        availableDrivers();
    }
}

bool OrmDb::throwError(const QSqlError &err)
{
    QString str;
    bool ret = false;
    if(err.isValid()) {     //发生错误时isValid()返回true
        switch (err.type()) {
        case QSqlError::NoError: str = "NoError"; ret = true; break;
        case QSqlError::UnknownError: str = "UnknownError"; break;
        case QSqlError::ConnectionError: str = "ConnectionError";break;
        case QSqlError::StatementError: str = "StatementError"; break;
        case QSqlError::TransactionError: str = "TransactionError"; break;
        } if(!ret) qCritical() << "sqlite error: " << tableName() << err.type() << str << err.text();
    } else ret = true;

    return ret;
}


bool OrmDb::sqlQuery(QSqlQuery &query)
{
    query.setForwardOnly(true); bool ret = query.exec();
    if(!ret) ret = throwError(query.lastError());
    return ret;
}

bool OrmDb::sqlQuery(QSqlQuery &query, const QString &sql)
{
    bool ret = query.prepare(sql);
    if(ret) ret = sqlQuery(query);
    if(!ret) qDebug() << sql << throwError(query.lastError());
    return ret;
}

bool OrmDb::sqlQuery(const QString &sql)
{
    QSqlQuery query(sDb);
    return sqlQuery(query, sql);
}


QJsonObject OrmDb::getObject(const QJsonObject &object, const QString &key)
{
    QJsonObject obj; if (object.contains(key)){
        QJsonValue value = object.value(key);
        if (value.isObject()) obj = value.toObject();
    }
    return obj;
}

QJsonArray OrmDb::getArray(const QJsonObject &object, const QString &key)
{
    QJsonArray array; if (object.contains(key)) {
        QJsonValue value = object.value(key);
        if (value.isArray())  array = value.toArray();
    }

    return array;
}


double OrmDb::getData(const QJsonObject &object, const QString &key)
{
    double ret = -1; if (object.contains(key))  {
        ret = object.value(key).toDouble();
    }

    return ret;
}

QString OrmDb::getString(const QJsonObject &object, const QString &key)
{
    QString str; if (object.contains(key)) {
        str = object.value(key).toString();
    }

    return str;
}
