#INCLUDEPATH += $$PWD

# include(orm/orm.pri)

HEADERS += \
    $$PWD/pdu_alarmsql.h \
    $$PWD/pdu_elesql.h \
    $$PWD/pdu_eventsql.h \
    $$PWD/pdu_hdasql.h \
    $$PWD/pdu_indexsql.h \
    $$PWD/pdualarmmodel.h \
    $$PWD/pduelemodel.h \
    $$PWD/pdueventmodel.h \
    $$PWD/pduhdamodel.h \
    $$PWD/pduindexmodel.h

SOURCES += \
    $$PWD/pdu_alarmsql.cpp \
    $$PWD/pdu_elesql.cpp \
    $$PWD/pdu_eventsql.cpp \
    $$PWD/pdu_hdasql.cpp \
    $$PWD/pdu_indexsql.cpp \
    $$PWD/pdualarmmodel.cpp \
    $$PWD/pduelemodel.cpp \
    $$PWD/pdueventmodel.cpp \
    $$PWD/pduhdamodel.cpp \
    $$PWD/pduindexmodel.cpp
