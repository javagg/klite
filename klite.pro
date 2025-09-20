include(klite.pri)

TEMPLATE = subdirs

SUBDIRS = \
  tl \
  gsi \
  db \
  pex \
  rdb \
  lib \
  plugins \
  # unit_tests \
  # buddies \
  lym \
  laybasic \
  layview \
  ant \
  img \
  edt \
  main \
  test \

tl.subdir = $$KY_SRC/tl
gsi.subdir = $$KY_SRC/gsi
db.subdir = $$KY_SRC/db
pex.subdir = $$KY_SRC/pex
rdb.subdir = $$KY_SRC/rdb
lib.subdir = $$KY_SRC/lib
plugins.subdir = $$KY_SRC/plugins
lym.subdir = $$KY_SRC/lym
laybasic.subdir = $$KY_SRC/laybasic
layview.subdir = $$KY_SRC/layview
ant.subdir = $$KY_SRC/ant
img.subdir = $$KY_SRC/img
edt.subdir = $$KY_SRC/edt

!equals(HAVE_QT, "0") {
  SUBDIRS += \
    # klayout_main \
    lay \
    layui \
    # fontgen \
    # doc \
    # icons \
}

lay.subdir = $$KY_SRC/lay
layui.subdir = $$KY_SRC/layui

LANG_DEPENDS =
# MAIN_DEPENDS =

SUBDIRS += rbastub
rbastub.depends += gsi
LANG_DEPENDS += rbastub

rbastub.subdir = $$KY_SRC/rbastub

SUBDIRS += pyastub
pyastub.depends += gsi
LANG_DEPENDS += pyastub

pyastub.subdir = $$KY_SRC/pyastub

gsi.depends += tl
db.depends += gsi
pex.depends += db
rdb.depends += db
lib.depends += db

lym.depends += gsi $$LANG_DEPENDS

laybasic.depends += rdb pex
layview.depends += laybasic

ant.depends += layview
img.depends += layview
edt.depends += layview

plugins.depends += lib

!equals(HAVE_QT, "0") {
  layui.depends += laybasic
  layview.depends += layui
  lay.depends += ant img edt layui lym
  plugins.depends += lay
} else {
  plugins.depends += layview ant img edt
}

!equals(HAVE_QT, "0") {
  SUBDIRS += main

  main.depends += layview plugins
}

wasm {
  QMAKE_CFLAGS += -s USE_ZLIB=1
  QMAKE_CXXFLAGS += -s USE_ZLIB=1
  QMAKE_LFLAGS += -s USE_ZLIB=1
}
