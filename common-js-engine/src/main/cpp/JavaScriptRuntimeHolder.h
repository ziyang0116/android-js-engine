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

        std::shared_ptr<facebook::jsi::Runtime> getJavaScriptRuntime() {
            return mJavaScriptRuntime;
        }

    protected:
        JavaScriptRuntimeHolder(std::shared_ptr<facebook::jsi::Runtime> runtime)
                : mJavaScriptRuntime(runtime) {}

    private:
        std::shared_ptr<facebook::jsi::Runtime> mJavaScriptRuntime;
    };

}

