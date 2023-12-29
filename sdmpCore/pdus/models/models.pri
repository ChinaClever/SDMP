#INCLUDEPATH += $$PWD

# include(orm/orm.pri)

HEADERS += \
    $$PWD/pdualarmmodel.h \
    $$PWD/pdualarmsql.h \
    $$PWD/pduelemodel.h \
    $$PWD/pduelesql.h \
    $$PWD/pdueventmodel.h \
    $$PWD/pdueventsql.h \
    $$PWD/pduhdamodel.h \
    $$PWD/pduhdasql.h \
    $$PWD/pduindexmodel.h \
    $$PWD/pduindexsql.h

SOURCES += \
    $$PWD/pdualarmmodel.cpp \
    $$PWD/pdualarmsql.cpp \
    $$PWD/pduelemodel.cpp \
    $$PWD/pduelesql.cpp \
    $$PWD/pdueventmodel.cpp \
    $$PWD/pdueventsql.cpp \
    $$PWD/pduhdamodel.cpp \
    $$PWD/pduhdasql.cpp \
    $$PWD/pduindexmodel.cpp \
    $$PWD/pduindexsql.cpp
