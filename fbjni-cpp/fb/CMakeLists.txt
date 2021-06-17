cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_library(fb SHARED
        assert.cpp
        jni/ByteBuffer.cpp
        jni/Countable.cpp
        jni/Environment.cpp
        jni/Exceptions.cpp
        jni/fbjni.cpp
        jni/Hybrid.cpp
        jni/jni_helpers.cpp
        jni/LocalString.cpp
        jni/OnLoad.cpp
        jni/ReadableByteChannel.cpp
        jni/References.cpp
        jni/WeakReference.cpp
        log.cpp
        lyra/lyra.cpp
        onload.cpp)

target_compile_options(fb PRIVATE -DLOG_TAG=\"libfb\" -DDISABLE_CPUCAP -DDISABLE_XPLAT -fexceptions -frtti -Oz -fvisibility=hidden -fvisibility-inlines-hidden -g)

find_library(log-lib log)

target_link_libraries(fb
        ${log-lib}
        -Wl,-hash-style=sysv)

target_include_directories(fb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)