INCLUDEPATH += $$PWD

QT += httpserver
include(httpclient/http.pri)

HEADERS += \
    # $$PWD/httpclient.h \
    $$PWD/httpserverobj.h

SOURCES += \
    $$PWD/httpserverobj.cpp

RESOURCES += \
    $$PWD/assets/certificate.crt \
    $$PWD/assets/private.key
