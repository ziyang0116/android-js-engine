#pragma once

#include <jsi/jsi.h>
#include <fb/fbjni.h>

using namespace facebook::jni;

namespace jsengine {

    template<typename K, typename V>
    struct JHashMap : public JavaClass<JHashMap<K, V>, JMap<K, V>> {
        constexpr static auto kJavaDescriptor = "Ljava/util/HashMap;";
    };

    template<typename E>
    struct JArrayList : public JavaClass<JArrayList<E>, JList<E>> {
        constexpr static auto kJavaDescriptor = "Ljava/util/ArrayList;";
    };

    facebook::jsi::Value valueFromJObject(
            facebook::jsi::Runtime &runtime,
            alias_ref<JObject> jObject);

    local_ref<JObject> jObjectFromValue(
            facebook::jsi::Runtime &runtime,
            const facebook::jsi::Value &value);

}
