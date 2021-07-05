#include <memory>

#include <fb/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

namespace jsengine {

    class JavaScriptRuntimeHolder : public facebook::jni::HybridClass<JavaScriptRuntimeHolder> {
    public:
        static constexpr auto kJavaDescriptor =
                "Lcom/jsengine/JavaScriptRuntime;";

        virtual std::shared_ptr<facebook::jsi::Runtime> getJavaScriptRuntime()=0;

    protected:
        JavaScriptRuntimeHolder() {}

    };

}

