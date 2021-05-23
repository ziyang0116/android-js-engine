#include "JSIConvert.h"

#include <jsi/jsi.h>
#include <fb/fbjni.h>

using namespace facebook::jsi;
using namespace facebook::jni;

namespace jsengine {

    Value valueFromJObject(Runtime &runtime, alias_ref<JObject> jObject) {
        if (jObject->isInstanceOf(JBoolean::javaClassStatic())) {
            JBoolean *jBoolean = static_cast<JBoolean *>(jObject.operator->());
            return jBoolean->booleanValue() == JNI_TRUE;
        } else if (jObject->isInstanceOf(JString::javaClassStatic())) {
            JString *jString = static_cast<JString *>(jObject.operator->());
            return String::createFromUtf8(runtime, jString->toStdString());
        } else if (jObject->isInstanceOf(JDouble::javaClassStatic())) {
            JDouble *jDouble = static_cast<JDouble *>(jObject.operator->());
            return jDouble->value();
        } else if (jObject->isInstanceOf(JInteger::javaClassStatic())) {
            JInteger *jInteger = static_cast<JInteger *>(jObject.operator->());
            return jInteger->value();
        } else if (jObject->isInstanceOf(JList<jstring>::javaClassStatic())) {
            JList<jstring> *jlist = static_cast<JList<jstring> *>(jObject.operator->());
            Array ret = Array(runtime, jlist->size());
            int i = 0;
            for (auto &elem : *jlist) {
                ret.setValueAtIndex(runtime, i, elem->toStdString());
                ++i;
            }
            return std::move(ret);
        } else if (jObject->isInstanceOf(JMap<jstring, jstring>::javaClassStatic())) {
            JMap<jstring, jstring> *jmap = static_cast<JMap<jstring, jstring> *>(jObject.operator->());
            Object ret(runtime);
            for (const auto &entry : *jmap) {
                if (entry.first) {
                    ret.setProperty(
                            runtime,
                            PropNameID::forUtf8(runtime, entry.first->toStdString()),
                            entry.second->toStdString());
                }
            }
            return std::move(ret);
        } else {
            throw JSError(runtime, "can not convert to JSI value, unknown jobject type");
        }
    }

    local_ref<JObject> jObjectFromValue(Runtime &runtime, const Value &value) {
        if (value.isUndefined() || value.isNull()) {
            return nullptr;
        } else if (value.isBool()) {
            return JBoolean::valueOf(value.getBool());
        } else if (value.isNumber()) {
            return JDouble::valueOf(value.getNumber());
        } else if (value.isString()) {
            return make_jstring(value.getString(runtime).utf8(runtime));
        } else {
            Object obj = value.getObject(runtime);
            if (obj.isArray(runtime)) {
                Array array = obj.getArray(runtime);
                static auto listCtor = JArrayList<JObject>::javaClassStatic()->
                        getConstructor<JArrayList<JObject>::javaobject()>();
                auto jlist = JArrayList<JObject>::javaClassStatic()->newObject(
                        listCtor);
                auto addMethod =
                        JArrayList<JObject>::javaClassStatic()->getMethod<jboolean(
                                local_ref<JObject>)>("add");
                for (size_t i = 0; i < array.size(runtime); ++i) {
                    addMethod(jlist,
                              jObjectFromValue(runtime, array.getValueAtIndex(runtime, i)));
                }
                return jlist;
            } else if (obj.isFunction(runtime)) {
                throw JSError(runtime, "JS Functions are not convertible to JObject");
            } else {
                static auto mapCtor = JHashMap<JString, JObject>::javaClassStatic()->
                        getConstructor<JHashMap<JString, JObject>::javaobject()>();
                auto map = JHashMap<JString, JObject>::javaClassStatic()->newObject(
                        mapCtor);
                auto putMethod =
                        JHashMap<JString, JObject>::javaClassStatic()->getMethod<jobject(
                                local_ref<JObject>, local_ref<JObject>)>("put");
                Array names = obj.getPropertyNames(runtime);
                for (size_t i = 0; i < names.size(runtime); ++i) {
                    String name = names.getValueAtIndex(runtime, i).getString(runtime);
                    Value prop = obj.getProperty(runtime, name);
                    if (prop.isUndefined()) {
                        continue;
                    }
                    // The JSC conversion uses JSON.stringify, which substitutes
                    // null for a function, so we do the same here.  Just dropping
                    // the pair might also work, but would require more testing.
                    if (prop.isObject() && prop.getObject(runtime).isFunction(runtime)) {
                        prop = Value::null();
                    }
                    putMethod(map, make_jstring(name.utf8(runtime)),
                              jObjectFromValue(runtime, std::move(prop)));
                }
                return map;
            }
        }
    }

}
