#ifndef PDU_HTTPSERVER_H
#define PDU_HTTPSERVER_H
#include "pdu_mqttpublish.h"

class Pdu_HttpServer : public HttpServerObj
{
public:
    explicit Pdu_HttpServer(QObject *parent = nullptr);

private:
    void pdu_keyList();
    void pdu_meta();
    void pdu_data();
    void pdu_line();
    void pdu_loop();
    void pdu_outlet();
    void pdu_group();
    void pdu_env();
    void pdu_tg();
    void pdu_number();
    void pdu_keyByIp();
    void pdu_dataByIp();
    void pdu_keyToIpList();
    void pdu_httpInit();
    void pdu_offline();
    void pdu_online();
    void pdu_alarm();
    void pdu_delete();
    void pdu_initObj();

private:
    Pdu_NetJsonPack *mNetJson=nullptr;
};

#endif // PDU_HTTPSERVER_H
