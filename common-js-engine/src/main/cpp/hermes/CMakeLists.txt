cmake_minimum_required(VERSION 3.4.1)

add_library(
        hermes-runtime
        SHARED
        OnLoad.cpp)


find_library(
        log-lib
        log)

target_link_libraries(
        hermes-runtime
        fb
        jsi
        hermes
        javascript-lib
        ${log-lib})


target_include_directories(
        hermes-runtime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${lib_src_dir}/jsi
        ${root_dir}/node_modules/hermes-engine/android/include)

target_compile_options(hermes-runtime PRIVATE -fexceptions -frtti -Oz -fvisibility=hidden -fvisibility-inlines-hidden -g)
