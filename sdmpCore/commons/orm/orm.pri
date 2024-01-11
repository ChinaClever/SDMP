INCLUDEPATH += $$PWD
QT += concurrent sql


INCLUDEPATH += $$PWD/include/
LIBS += -L$$PWD/lib
LIBS += -lQxOrm



HEADERS += \
    $$PWD/export.h \
    $$PWD/ormdb.h \
    $$PWD/ormobj.h \
    $$PWD/precompiled.h

SOURCES += \
    $$PWD/ormdb.cpp \
    $$PWD/ormobj.cpp



