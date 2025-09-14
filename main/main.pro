DESTDIR = $$OUT_PWD/../..
TARGET = klite_main

include($$PWD/../klite.pri)

QT       += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

HEADERS += \

INCLUDEPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC
DEPENDPATH += $$LAYVIEW_INC $$LAYBASIC_INC $$LAYUI_INC $$TL_INC $$GSI_INC $$DB_INC $$RDB_INC

KL_DESTDIR = $$OUT_PWD/../$$KY_SRC
# message($$KL_DESTDIR)

LIBS += -L$$DESTDIR -L$$KL_DESTDIR -lklayout_layview  -lklayout_laybasic -lklayout_layui -lklayout_tl -lklayout_gsi -lklayout_db -lklayout_rdb

