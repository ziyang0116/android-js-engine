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
       onload.cpp )

target_compile_options(fb PRIVATE -DDISABLE_CPUCAP -DDISABLE_XPLAT -fexceptions -frtti)

#查找log库
find_library(log-lib log)

target_link_libraries(fb
        ${log-lib}
        )
# copy out the lib binary... need to leave the static lib around to pass gradle check
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../distribution)
set_target_properties(fb
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY
                      "${distribution_DIR}/fb/lib/${ANDROID_ABI}")


target_include_directories(fb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)