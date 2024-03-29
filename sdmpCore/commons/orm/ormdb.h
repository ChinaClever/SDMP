#ifndef ORMDB_H
#define ORMDB_H
#include "precompiled.h"
#include "cfgcom.h"


class OrmDb
{
public:
    explicit OrmDb(); ~OrmDb();
    virtual QString tableName() = 0;

    bool sql_remove(int id);
    bool sql_removeMinIds(int id);
    bool sql_removeMaxIds(int id);
    bool sql_remove(const QString &condition);
    bool sql_remove(const QString &name, const QString &vale);

    quint64 sql_maxId();
    quint64 sql_id_select(const QString &sql);
    quint64 sql_maxId(const QString &condition);
    quint64 sql_maxId(const QString &column_name, const QString &condition);

    int sql_minId();
    int sql_minId(const QString &condition);
    int sql_minId(const QString &column_name, const QString &condition);

    int sql_counts();
    int sql_counts(const QString &name);
    int sql_contains(const QString &name, const QString &value);
    int sql_counts(const QString &column_name, const QString &condition);
    bool sql_countsRemove(int count);
    QDateTime sql_updateTime();

    static bool isOpen() {return initDb();}
    bool sql_updateColumn(const QString& column_name, QString value, const QString &condition);
    bool sql_updateColumn(const QString& column_name, double value, const QString &condition);
    QVariantList sql_listColumn(const QString &column_name, const QString &condition);
    QVariantList sql_selectIds(const QString &condition="");
    QJsonArray getArray(const QJsonObject &object, const QString &key);
    QJsonObject getObject(const QJsonObject &object, const QString &key);
    QString getString(const QJsonObject &object, const QString &key);
    double getData(const QJsonObject &object, const QString &key);
    quint64 get_max_id() {return m_max_id;}
    quint64 get_cnt() {return m_cnt;}
    static QStringList sql_error();
    virtual int workDown(){return 0;}

    bool isTableExists();
    bool sql_clear();
    void mdelay(int msec);

protected:
    static bool initDb();
    static void initDebugInfo();
    static bool availableDrivers();
    bool sqlQuery(QSqlQuery &query);
    bool sqlQuery(const QString &sql);
    bool sqlQuery(QSqlQuery &query, const QString &sql);
    void setTableMarking(const QString& marking);
    bool throwError(const QSqlError &err);

protected:
    static QSqlDatabase sDb;
    static QStringList mSqlErrorLst;
    quint64 m_max_id=0;
    quint64 m_cnt=0;
    // static QMutex msLock;
};

#endif // ORMDB_H
