#include <string>
#include <memory>

#include <fb/fbjni.h>
#include <fb/fbjni/Hybrid.h>
#include <fb/log.h>

#include <hermes/hermes.h>

#include "JavaScriptRuntimeHolder.h"

using namespace facebook::jni;

namespace jsengine {
    class HermesRuntimeHolder
            : public facebook::jni::HybridClass<HermesRuntimeHolder, JavaScriptRuntimeHolder> {
    public:

        static constexpr auto kJavaDescriptor =
                "Lcom/jsengine/hermes/HermesRuntime;";

        static facebook::jni::local_ref<jhybriddata> initHybridDefaultConfig(
                facebook::jni::alias_ref<jclass>) {
            return makeCxxInstance(facebook::hermes::makeHermesRuntime());
        }

        static void registerNatives() {
            registerHybrid(
                    {
                            makeNativeMethod(
                                    "initHybridDefaultConfig",
                                    HermesRuntimeHolder::initHybridDefaultConfig)
                    });
        }

    private:
        friend HybridBase;
        using HybridBase::HybridBase;
    };
}
