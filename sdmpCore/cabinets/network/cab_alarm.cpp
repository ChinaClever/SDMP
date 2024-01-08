/*
 *
 *  Created on: 2025年1月1日
 *      Author: Lzy
 */
#include "cab_alarm.h"
#include "http.h"

Cab_Alarm::Cab_Alarm() {}


Cab_Alarm *Cab_Alarm::bulid()
{
    static Cab_Alarm* sington = nullptr;
    if(!sington) sington = new Cab_Alarm();
    return sington;
}


void Cab_Alarm::http_post(const QJsonObject &obj)
{
    sCfgLogItem *it = &CfgCom::mCfgLog;
    if(!it->en) return;

    QJsonDocument jsonDocument(obj);
    QByteArray body = jsonDocument.toJson();

    QUrl url(it->url); // "https://some.domain.url/"
    auto reply = Http::instance().post(url, body, "application/json");
    QObject::connect(reply, &HttpReply::finished, [&](auto &reply) {
        if (reply.isSuccessful()) {
            qDebug() << "Feel the bytes!" << reply.body();
        } else {
            cout << "Something's wrong here" << reply.statusCode() << reply.reasonPhrase();
        }
    });
}


void Cab_Alarm::alarmWork()
{
    Cab_HdaSql *hdaSql = Cab_HdaSql::bulid();
    Cab_IndexSql *cabSql = Cab_IndexSql::bulid();
    QList<uint> cab_ids = cabSql->getIds();
    foreach (const auto id, cab_ids) {
        int is_disabled = cabSql->is_disabled(id);
        double tg_pow = hdaSql->tgApparentPower(id);
        double cab_pow = cabSql->pow_capacity(id);
        if((is_disabled && (tg_pow > 0))  || (tg_pow > cab_pow)) {
            QJsonObject obj; obj.insert("cab_id", (int)id);
            obj.insert("pow_capacity", cab_pow);
            obj.insert("apparent_power", tg_pow);
            obj.insert("is_disabled", is_disabled);
            http_post(obj);
        }
    }
}
