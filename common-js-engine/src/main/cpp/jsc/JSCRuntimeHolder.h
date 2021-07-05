#include <string>
#include <memory>

#include <fb/fbjni.h>
#include <fb/fbjni/Hybrid.h>
#include <fb/log.h>

#include "JavaScriptRuntimeHolder.h"
#include "JSCRuntime.h"

using namespace facebook::jni;

namespace jsengine {
    class JSCRuntimeHolder
            : public facebook::jni::HybridClass<JSCRuntimeHolder, JavaScriptRuntimeHolder> {
    public:

        static constexpr auto kJavaDescriptor =
                "Lcom/jsengine/jsc/JSCRuntime;";

        static facebook::jni::local_ref<jhybriddata> initHybridDefaultConfig(
                facebook::jni::alias_ref<jclass>) {
            return makeCxxInstance();
        }

        std::shared_ptr<facebook::jsi::Runtime> getJavaScriptRuntime(){
            return facebook::jsc::makeJSCRuntime();
        }

        static void registerNatives() {
            registerHybrid(
                    {
                            makeNativeMethod(
                                    "initHybridDefaultConfig",
                                    JSCRuntimeHolder::initHybridDefaultConfig)
                    });
        }

    private:
        friend HybridBase;
        using HybridBase::HybridBase;
    };
}
