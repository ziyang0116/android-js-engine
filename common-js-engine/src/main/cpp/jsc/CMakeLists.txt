cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_library(jsc-runtime
        SHARED
        JSCRuntime.cpp
        OnLoad.cpp)

target_link_libraries(jsc-runtime
        fb
        jsi
        jsc
        javascript-lib)

target_include_directories(jsc-runtime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${lib_src_dir}/jsi
        ${third_party_dir}/jsc)
