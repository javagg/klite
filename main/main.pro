DESTDIR = $$OUT_PWD/../..
TARGET = klite_main

include($$PWD/../klite.pri)

QT       += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    other.cpp \
    main.cpp \


HEADERS += \
    other.h \

RESOURCES += main.qrc

INCLUDEPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC
DEPENDPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC

KL_DESTDIR = $$OUT_PWD/../$$KY_SRC

LIBS += -L$$DESTDIR -L$$KL_DESTDIR -lklayout_laybasic  -lklayout_tl -lklayout_gsi -lklayout_db -lklayout_rdb -lklayout_layui -lklayout_layview

# for plugins
INCLUDEPATH += $$PWD/../$$KY_SRC/plugins/common $$PWD/../$$KY_SRC/plugins/streamers/gds2/db_plugin
LIBS += -L$$KL_DESTDIR/db_plugins -lgds2

wasm {
  QMAKE_CFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING
  QMAKE_CXXFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING
  QMAKE_LFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING --pre-js $$PWD/pre.js
}
