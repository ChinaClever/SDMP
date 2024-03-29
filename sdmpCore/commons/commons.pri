#INCLUDEPATH += $$PWD

include(cfg/cfg.pri)
include(orm/orm.pri)
include(http/http.pri)
include(mqtt/mqtt.pri)
include(qxlsx/qxlsx.pri)
include(single/single.pri)
include(msgcom/msgcom.pri)
include(tabcom/tabcom.pri)
include(QtRedis/QtRedis.pri)
include(backcolour/backcolour.pri)

HEADERS += \
    $$PWD/print.h

SOURCES += \
    $$PWD/print.cpp
