include($$PWD/../klite.pri)

QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += \
  ../main/other.cpp \
  tst_tl.cpp \

HEADERS += \
   ../main/other.h \

RESOURCES += ../main/main.qrc

INCLUDEPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC
DEPENDPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC

DESTDIR = $$OUT_PWD/../..

KL_DESTDIR = $$OUT_PWD/../$$KY_SRC

LIBS += -L$$DESTDIR -L$$KL_DESTDIR  -lklayout_tl -lklayout_gsi -lklayout_db -lklayout_rdb -lklayout_layview

# for plugins
INCLUDEPATH += $$PWD/../$$KY_SRC/plugins/common $$PWD/../$$KY_SRC/plugins/streamers/gds2/db_plugin
LIBS += -L$$KL_DESTDIR/db_plugins -lgds2

wasm {
  QMAKE_CFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING
  QMAKE_CXXFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING
  QMAKE_LFLAGS += -sNO_DISABLE_EXCEPTION_CATCHING
}
