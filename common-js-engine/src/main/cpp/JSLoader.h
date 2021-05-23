// Copyright (c) Facebook, Inc. and its affiliates.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <string>

#include <android/asset_manager.h>
#include <fb/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

namespace jsengine {

    struct JAssetManager : facebook::jni::JavaClass<JAssetManager> {
        static constexpr auto kJavaDescriptor = "Landroid/content/res/AssetManager;";
    };

    AAssetManager *
    extractAssetManager(facebook::jni::alias_ref<JAssetManager::javaobject> assetManager);

    std::shared_ptr<const Buffer>
    loadScript(AAssetManager *assetManager, const std::string &assetName);

}
