#pragma once

#include <android/log.h>
#include <string>

namespace jsengine {

    __attribute__((visibility("default"))) void reactAndroidLoggingHook(
            const std::string &message,
            android_LogPriority logLevel);

    __attribute__((visibility("default"))) void reactAndroidLoggingHook(
            const std::string &message,
            unsigned int logLevel);

}
