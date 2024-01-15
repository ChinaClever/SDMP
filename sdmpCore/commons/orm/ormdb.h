#ifndef ORMDB_H
#define ORMDB_H
#include "precompiled.h"
#include "cfgcom.h"


class OrmDb
{
public:
    explicit OrmDb();
    virtual QString tableName() = 0;

    bool sql_remove(int id);
    bool sql_removeMinIds(int id);
    bool sql_removeMaxIds(int id);
    bool sql_remove(const QString &condition);
    bool sql_remove(const QString &name, const QString &vale);

    int sql_maxId();
    int sql_id_select(const QString &sql);
    int sql_maxId(const QString &condition);
    int sql_maxId(const QString &column_name, const QString &condition);

    int sql_minId();
    int sql_minId(const QString &condition);
    int sql_minId(const QString &column_name, const QString &condition);

    int sql_counts();
    int sql_counts(const QString &name);
    int sql_contains(const QString &name, const QString &value);
    int sql_counts(const QString &column_name, const QString &condition);
    bool sql_countsRemove(int count);
    QDateTime sql_updateTime();

    bool sql_updateColumn(const QString& column_name, QString value, const QString &condition);
    bool sql_updateColumn(const QString& column_name, double value, const QString &condition);
    QVariantList sql_listColumn(const QString &column_name, const QString &condition);
    QVariantList sql_selectIds(const QString &condition="");
    QJsonArray getArray(const QJsonObject &object, const QString &key);
    QJsonObject getObject(const QJsonObject &object, const QString &key);
    QString getString(const QJsonObject &object, const QString &key);
    double getData(const QJsonObject &object, const QString &key);

    bool isTableExists();
    bool sql_clear();
    void mdelay(int msec);

protected:
    void initDb();
    void initDebugInfo();
    bool availableDrivers();
    bool sqlQuery(QSqlQuery &query);
    bool sqlQuery(const QString &sql);
    bool sqlQuery(QSqlQuery &query, const QString &sql);
    void setTableMarking(const QString& marking);
    bool throwError(const QSqlError &err);

protected:
    static QSqlDatabase sDb;
    // static QMutex msLock;
};

#endif // ORMDB_H
