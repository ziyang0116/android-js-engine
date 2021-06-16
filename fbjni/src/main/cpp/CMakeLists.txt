cmake_minimum_required(VERSION 3.4.1)

project("cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++1y")

set(CMAKE_VERBOSE_MAKEFILE on)

set(lib_src_dir ${CMAKE_CURRENT_SOURCE_DIR})

set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)

set(third_party_lib ${root_dir}/fbjni-cpp)

set(lib_build_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../build/tmp/${ANDROID_ABI})

file(MAKE_DIRECTORY ${lib_build_dir})

add_subdirectory(${third_party_lib}/fb ${lib_build_dir}/fb)
