cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_library(v8-runtime SHARED
        HostProxy.cpp
        JSIV8ValueConverter.cpp
        V8PointerValue.cpp
        V8Runtime.cpp
        OnLoad.cpp)

if(${ANDROID_ABI} STREQUAL "arm64-v8a" OR ${ANDROID_ABI} STREQUAL  "x86_64")
    target_compile_options(v8-runtime PRIVATE -DV8_COMPRESS_POINTERS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${third_party_dir}/v8/include)

target_link_libraries(v8-runtime
        v8android
        fb
        jsi
        javascript-lib)
