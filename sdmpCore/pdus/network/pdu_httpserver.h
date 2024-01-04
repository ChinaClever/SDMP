#ifndef PDU_HTTPSERVER_H
#define PDU_HTTPSERVER_H

#include "httpserverobj.h"
#include "pdu_netjsonpack.h"

class Pdu_HttpServer : public HttpServerObj
{
public:
    explicit Pdu_HttpServer(QObject *parent = nullptr);

private:
    void pdu_keys();
    void pdu_meta();
    void pdu_data();
    void pdu_line();
    void pdu_loop();
    void pdu_outlet();
    void pdu_group();
    void pdu_env();
    void pdu_tg();
    void pdu_httpInit();
    void pdu_offline();
    void pdu_online();
    void pdu_alarm();
    void pdu_delete();

private:
    Pdu_NetJsonPack *mNetJson;
};

#endif // PDU_HTTPSERVER_H
