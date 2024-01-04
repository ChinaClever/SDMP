#INCLUDEPATH += $$PWD

# include(orm/orm.pri)

HEADERS += \
    $$PWD/pdu_elesql.h \
    $$PWD/pdu_hdasql.h \
    $$PWD/pdu_indexsql.h \
    $$PWD/pdu_logsql.h \
    $$PWD/pduelemodel.h \
    $$PWD/pduhdamodel.h \
    $$PWD/pduindexmodel.h \
    $$PWD/pdulogmodel.h

SOURCES += \
    $$PWD/pdu_elesql.cpp \
    $$PWD/pdu_hdasql.cpp \
    $$PWD/pdu_indexsql.cpp \
    $$PWD/pdu_logsql.cpp \
    $$PWD/pduelemodel.cpp \
    $$PWD/pduhdamodel.cpp \
    $$PWD/pduindexmodel.cpp \
    $$PWD/pdulogmodel.cpp
