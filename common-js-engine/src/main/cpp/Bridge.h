
#include <string>

#include <fb/fbjni.h>
#include <fb/fbjni/Hybrid.h>

#include "JavaScriptRuntimeHolder.h"
#include "JSLogging.h"
#include "JSLoader.h"


using namespace facebook::jni;
using namespace facebook::jsi;

namespace jsengine {

    struct JJSCallback : public JavaClass<JJSCallback> {
        constexpr static auto kJavaDescriptor = "Lcom/jsengine/JSCallback;";
    };

    class Bridge : public facebook::jni::HybridClass<Bridge> {
    public:
        static constexpr auto kJavaDescriptor = "Lcom/jsengine/Bridge;";

        static facebook::jni::local_ref<jhybriddata>
        initHybrid(facebook::jni::alias_ref<jclass>);

        ~Bridge() override;

        static void registerNatives();


    private:
        friend HybridBase;

        Bridge();

        void initializeBridge(JavaScriptRuntimeHolder *javaScriptRuntimeHolder);

        void loadScriptFromString(const std::string &jsString);

        void loadScriptFromAssets(alias_ref<JAssetManager::javaobject> assetManager,
                                  const std::string &assetName);

        local_ref<JObject>
        jniCallJSFunctionSync(const std::string jsFunction, alias_ref<JObject> jObject);

        void jniCallJSFunction(const std::string jsFunction, alias_ref<JObject> jObject,
                               alias_ref<JJSCallback> callback);

        void setGlobalVariable(std::string propName, std::string &&jsonValue);

//            jlong getJavaScriptContext();

        // This should be the only long-lived strong reference, but every C++ class
        // will have a weak reference.
        std::shared_ptr<Runtime> instance;

        void bindNativeLogger();
    };
}
