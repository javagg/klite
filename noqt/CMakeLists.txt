cmake_minimum_required(VERSION 3.16)

project(klayout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(K_SRC_DIR ${CMAKE_SOURCE_DIR}/../3p/kl/src)
list(APPEND K_INCS ${K_SRC_DIR}/tl/tl)

message(STATUS "K_INCS is: ${K_INCS}")

include_directories(${K_INCS})

file(GLOB SRC_FILES "${K_SRC_DIR}/tl/tl/*.cc")

list(APPEND IGNORED_TL_SRC_FILES
    tlWebDAV.cc
    tlHttpStreamCurl.cc
    tlHttpStreamCurl.cc
    tlFileSystemWatcher.cc
    tlDeferredExecutionQt.cc
    tlHttpStreamQt.cc
)

list(TRANSFORM IGNORED_TL_SRC_FILES PREPEND "${K_SRC_DIR}/tl/tl/")

message(STATUS "IGNORED_SRC_FILES is: ${IGNORED_TL_SRC_FILES}")

list(REMOVE_ITEM SRC_FILES ${IGNORED_TL_SRC_FILES})

message(STATUS "MY_VARIABLE is: ${SRC_FILES}")

add_library(klayout STATIC ${SRC_FILES})

target_compile_definitions(klayout PRIVATE KLAYOUT_LIBRARY)

if(EMSCRIPTEN)
    target_compile_options(klayout PRIVATE "-sUSE_ZLIB=1")
endif()
