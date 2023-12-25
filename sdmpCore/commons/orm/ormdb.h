#ifndef ORMDB_H
#define ORMDB_H
#include "precompiled.h"

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

    bool sql_updateColumn(const QString& column_name, QString value, const QString &condition);
    bool sql_updateColumn(const QString& column_name, double value, const QString &condition);
    QVariantList sql_listColumn(const QString &column_name, const QString &condition);
    QVariantList sql_selectIds(const QString &condition="");

    bool isTableExists();
    bool sql_clear();

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
    static QSqlDatabase mDb;
};

#define cout qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << "[" << __FILE__ << ":" << Q_FUNC_INFO << ":" << __LINE__ << "]"

#endif // ORMDB_H
