#include <jni.h>
#include <string>
#include <fb/fbjni.h>
#include <fb/fbjni/Hybrid.h>
#include <memory>
#include <array>

#include "Bridge.h"
#include "JSLoader.h"
#include "JSIConvert.h"

using namespace facebook::jni;
using namespace facebook::jsi;


using Logger =
std::function<void(const std::string &message, unsigned int logLevel)>;

namespace jsengine {

    facebook::jni::local_ref<Bridge::jhybriddata> Bridge::initHybrid(
            facebook::jni::alias_ref<jclass>) {
        return makeCxxInstance();
    }

    Bridge::Bridge() {}

    Bridge::~Bridge() {
    }

    void Bridge::registerNatives() {
        registerHybrid({
                               makeNativeMethod("initHybrid", Bridge::initHybrid),
                               makeNativeMethod("initializeBridge", Bridge::initializeBridge),
                               makeNativeMethod("jniLoadScriptFromString",
                                                Bridge::loadScriptFromString),
                               makeNativeMethod("jniLoadScriptFromAssets",
                                                Bridge::loadScriptFromAssets),
                               makeNativeMethod("jniCallJSFunctionSync",
                                                Bridge::jniCallJSFunctionSync),
                               makeNativeMethod("jniCallJSFunction",
                                                Bridge::jniCallJSFunction),
                               makeNativeMethod("setGlobalVariable", Bridge::setGlobalVariable),
                       });
    }


    void Bridge::initializeBridge(
            JavaScriptRuntimeHolder *javaScriptRuntimeHolder) {
        instance = javaScriptRuntimeHolder->getJavaScriptRuntime();
        bindNativeLogger();
    }

    void Bridge::loadScriptFromString(const std::string &jsString) {

        std::shared_ptr<StringBuffer> buffer = std::make_shared<StringBuffer>(jsString);
        instance->evaluateJavaScript(buffer, "");
    }

    void Bridge::loadScriptFromAssets(alias_ref<JAssetManager::javaobject> assetManager,
                                      const std::string &assetURL) {
        const int kAssetsLength = 9;  // strlen("assets://");
        auto sourceURL = assetURL.substr(kAssetsLength);

        auto manager = extractAssetManager(assetManager);
        auto script = loadScript(manager, sourceURL);
        instance->evaluateJavaScript(script, assetURL);
    }

    local_ref<JObject>
    Bridge::jniCallJSFunctionSync(const std::string jsFunctionName, alias_ref<JObject> jObjet) {

        Function jsFunction =
                instance->global().getPropertyAsFunction(*instance, jsFunctionName.c_str());
        if (!jsFunction.isFunction(*instance)) {
            throw JSINativeException(
                    "is not js function");
        }
        Value ret = valueFromJObject(*instance, jObjet);
        Value result = jsFunction.call(*instance, ret);
        return jsengine::jObjectFromValue(*instance, result);
    }

    void Bridge::jniCallJSFunction(const std::string jsFunctionName, alias_ref<JObject> jObject,
                                   alias_ref<JJSCallback> jcallback) {
        typedef JJSCallback JSCallback;


        Function jsFunction =
                instance->global().getPropertyAsFunction(*instance, jsFunctionName.c_str());
        if (!jsFunction.isFunction(*instance)) {
            throw JSINativeException(
                    "is not js function");
        }
        Value ret = valueFromJObject(*instance, jObject);

        Function callback = Function::createFromHostFunction(
                *instance,
                PropNameID::forAscii(*instance, "callback"),
                2,
                [jcallback = std::move(jcallback)](
                        facebook::jsi::Runtime &runtime,
                        const facebook::jsi::Value &,
                        const facebook::jsi::Value *args,
                        size_t count) {
                    if (count != 1) {
                        throw std::invalid_argument(
                                "callback takes 1 arguments");
                    }
                    auto invokeMethod = JSCallback::javaClassStatic()->getMethod<void(
                            local_ref<JObject>)>("invoke");
                    invokeMethod(jcallback, jsengine::jObjectFromValue(runtime, args[0]));
                    return Value::undefined();
                });
        jsFunction.call(*instance, ret, callback);

    }

    void Bridge::setGlobalVariable(std::string propName, std::string &&jsonValue) {

    }

    void Bridge::bindNativeLogger() {
        Logger androidLogger =
                static_cast<void (*)(const std::string &, unsigned int)>(
                        &reactAndroidLoggingHook);
        instance->global().setProperty(
                *instance,
                "nativeLoggingHook",
                Function::createFromHostFunction(
                        *instance,
                        PropNameID::forAscii(*instance, "nativeLoggingHook"),
                        2,
                        [logger = std::move(androidLogger)](
                                facebook::jsi::Runtime &runtime,
                                const facebook::jsi::Value &,
                                const facebook::jsi::Value *args,
                                size_t count) {
                            if (count != 2) {
                                throw std::invalid_argument(
                                        "nativeLoggingHook takes 2 arguments");
                            }
                            logger(
                                    args[0].asString(runtime).utf8(runtime),
                                    args[1].asNumber());
                            return Value::undefined();
                        }));
    }
}
