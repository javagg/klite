cmake_minimum_required(VERSION 3.16)

project(klayout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(K_SRC_DIR ${CMAKE_SOURCE_DIR}/../3p/kl/src)
list(APPEND K_INCS
    ${K_SRC_DIR}/tl/tl
    ${K_SRC_DIR}/gsi/gsi
    ${K_SRC_DIR}/db/db
    ${K_SRC_DIR}/lib/lib
    ${K_SRC_DIR}/rdb/rdb
    ${K_SRC_DIR}/laybasic/laybasic
    ${K_SRC_DIR}/layview/layview
)

message(STATUS "K_INCS is: ${K_INCS}")

include_directories(${K_INCS})

file(GLOB SRC_FILES
    "${K_SRC_DIR}/tl/tl/*.cc"
    "${K_SRC_DIR}/db/db/*.cc"
    "${K_SRC_DIR}/gsi/gsi/*.cc"
    "${K_SRC_DIR}/lib/lib/*.cc"
    "${K_SRC_DIR}/laybasic/laybasic/*.cc"
    "${K_SRC_DIR}/layview/layview/*.cc"
)

list(APPEND IGNORED_TL_SRC_FILES
    tlWebDAV.cc
    tlHttpStreamCurl.cc
    tlFileSystemWatcher.cc
    tlDeferredExecutionQt.cc
    tlHttpStreamQt.cc
    tlGit.cc
)
list(APPEND IGNORED_LAYBASIC_SRC_FILES
    gtf.cc
    layPluginConfigPage.cc
    layProperties.cc
    layDragDropData.cc
    layCursor.cc
    laybasicForceLink.cc
)
list(APPEND IGNORED_LAYVIEW_SRC_FILES
    layGridNetConfigPage.cc
    layLayoutView_qt.cc
    gsiDeclLayLayoutView_qt.cc
    layviewForceLink.cc
)


list(TRANSFORM IGNORED_TL_SRC_FILES PREPEND "${K_SRC_DIR}/tl/tl/")
list(TRANSFORM IGNORED_LAYBASIC_SRC_FILES PREPEND "${K_SRC_DIR}/laybasic/laybasic/")
list(TRANSFORM IGNORED_LAYVIEW_SRC_FILES PREPEND "${K_SRC_DIR}/layview/layview/")

list(REMOVE_ITEM SRC_FILES ${IGNORED_TL_SRC_FILES} ${IGNORED_LAYBASIC_SRC_FILES} ${IGNORED_LAYVIEW_SRC_FILES})

if (DEFINED EMSCRIPTEN)
    add_executable(klayout main.cpp ${SRC_FILES})
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
    set_target_properties(klayout PROPERTIES COMPILE_FLAGS "-Os -s USE_ZLIB=1 -s SIDE_MODULE=1")
    set_target_properties(klayout PROPERTIES LINK_FLAGS    "-Os -s USE_ZLIB=1 -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
else()
    add_library(klayout STATIC ${SRC_FILES})
endif()
