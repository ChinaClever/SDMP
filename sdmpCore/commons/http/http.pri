#INCLUDEPATH += $$PWD

QT += httpserver

HEADERS += \
    $$PWD/httpserverobj.h

SOURCES += \
    $$PWD/httpserverobj.cpp

RESOURCES += \
    $$PWD/assets/certificate.crt \
    $$PWD/assets/private.key
