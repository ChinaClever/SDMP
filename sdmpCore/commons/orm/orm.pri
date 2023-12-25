INCLUDEPATH += $$PWD
QT += concurrent

#_BUILDING_USER，通过它可以知道项目是否正在编译
DEFINES += _BUILDING_APP

#包含模块的pri文件，一些宏定义使用中需要用到
include($$PWD/QxOrm/QxOrm.pri)

#添加源代码的头文件路劲，后面代码包含头文件的时候就可以使用相对路径了
INCLUDEPATH += $$PWD/QxOrm/include

#添加编译好的动态库，QxOrm源码编译的动态库在QxOrm/lib目录中，最好编译debug、release两个版本
LIBS += -L$$PWD/QxOrm/lib
CONFIG(debug, debug|release) {
    LIBS += -lQxOrmd
} else {
    LIBS +=  -lQxOrm
}


HEADERS += \
    $$PWD/export.h \
    $$PWD/ormdb.h \
    $$PWD/ormobj.h \
    $$PWD/precompiled.h

SOURCES += \
    $$PWD/ormdb.cpp \
    $$PWD/ormobj.cpp



