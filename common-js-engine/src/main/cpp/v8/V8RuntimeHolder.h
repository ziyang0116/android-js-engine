#pragma once

#include <memory.h>
#include "jsi/jsi.h"

#include <fb/fbjni.h>
#include <fb/fbjni/Hybrid.h>
#include <fb/log.h>

#include "V8Runtime.h"

#include "JavaScriptRuntimeHolder.h"

namespace jsengine {

    class V8RuntimeHolder
            : public facebook::jni::HybridClass<V8RuntimeHolder, JavaScriptRuntimeHolder> {
    public:

        static constexpr auto kJavaDescriptor =
                "Lcom/jsengine/v8/V8Runtime;";

        static facebook::jni::local_ref<jhybriddata> initHybrid(
                facebook::jni::alias_ref<jclass>, const std::string &timezoneId) {
            return makeCxxInstance(std::make_unique<facebook::V8Runtime>(timezoneId));
        }

        static void registerNatives() {
            registerHybrid(
                    {
                            makeNativeMethod(
                                    "initHybrid",
                                    V8RuntimeHolder::initHybrid)
                    });
        }

    private:
        friend HybridBase;
        using HybridBase::HybridBase;
    };
}
