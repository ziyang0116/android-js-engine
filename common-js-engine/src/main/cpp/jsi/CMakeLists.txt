cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

aux_source_directory(./jsi SRC_MAIN)

add_library(jsi STATIC
        ${SRC_MAIN})

target_include_directories(jsi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(jsi PRIVATE -fexceptions -frtti -Oz -fvisibility=hidden -fvisibility-inlines-hidden -g)

