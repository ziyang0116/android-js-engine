cmake_minimum_required(VERSION 3.4.1)

project("cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++1y")

set(CMAKE_VERBOSE_MAKEFILE on)

set(lib_src_dir ${CMAKE_CURRENT_SOURCE_DIR})

set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)

set(third_party_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../build/third-party-ndk)
set(third_party_lib ${lib_src_dir}/../jni/thirdparty)

set(lib_build_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../build/tmp/${ANDROID_ABI})
file(MAKE_DIRECTORY ${lib_build_dir})

add_library(hermes
        SHARED
        IMPORTED)

set_target_properties(
        hermes
        PROPERTIES IMPORTED_LOCATION
        ${third_party_dir}/hermes/jni/${ANDROID_ABI}/libhermes.so)

add_library(jsc
        SHARED
        IMPORTED)

set_target_properties(
        jsc
        PROPERTIES IMPORTED_LOCATION
        ${third_party_dir}/jsc/jni/${ANDROID_ABI}/libjsc.so)

add_library(
        v8android
        SHARED
        IMPORTED)
set_target_properties(
        v8android
        PROPERTIES IMPORTED_LOCATION
        ${third_party_dir}/v8/jni/${ANDROID_ABI}/libv8android.so)

add_subdirectory(${lib_src_dir}/jsi ${lib_build_dir}/jsi)
add_subdirectory(${third_party_lib}/fb ${lib_build_dir}/fb)
add_subdirectory(${lib_src_dir}/hermes ${lib_build_dir}/hermes)
add_subdirectory(${lib_src_dir}/jsc ${lib_build_dir}/jsc)
add_subdirectory(${lib_src_dir}/v8 ${lib_build_dir}/v8)

add_library(
        javascript-lib
        SHARED
        Bridge.cpp
        OnLoad.cpp
        JSLogging.cpp
        JSLoader.cpp
        JSIConvert.cpp)

find_library(
        android
        log-lib
        log)

target_link_libraries(
        javascript-lib
        android
        fb
        jsi
        log
        ${log-lib})

target_include_directories(
        javascript-lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${lib_src_dir}/jsi)