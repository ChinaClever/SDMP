
include(qmqtt/qmqtt.pri)


HEADERS += \
    $$PWD/mqtt_client.h \
    $$PWD/mqtt_publish.h

SOURCES += \
    $$PWD/mqtt_client.cpp \
    $$PWD/mqtt_publish.cpp


RESOURCES += \
    $$PWD/certs/cert.pem \
    $$PWD/certs/key.pem
