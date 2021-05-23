#include <memory>
#include <android/asset_manager_jni.h>
#include <fb/fbjni.h>
#include <fb/log.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <jsi/jsi.h>
#include "JSLoader.h"

using namespace facebook::jni;
using namespace facebook::jsi;

namespace jsengine {

    __attribute__((visibility("default")))
    AAssetManager *extractAssetManager(alias_ref<JAssetManager::javaobject> assetManager) {
        auto env = Environment::current();
        return AAssetManager_fromJava(env, assetManager.get());
    }

    __attribute__((visibility("default")))
    std::shared_ptr<const Buffer> loadScript(
            AAssetManager *manager,
            const std::string &assetName) {
        if (manager) {
            auto asset = AAssetManager_open(
                    manager,
                    assetName.c_str(),
                    AASSET_MODE_STREAMING); // Optimized for sequential read: see AssetManager.java for docs
            if (asset) {
                size_t fileLength = AAsset_getLength(asset);

                char *dataBuffer = new char[fileLength + 1];
                dataBuffer[fileLength] = 0;
                AAsset_read(asset, dataBuffer, fileLength);
                AAsset_close(asset);
                auto buff = std::make_shared<StringBuffer>(dataBuffer);
                delete[] dataBuffer;
                return buff;

            }
        }
        throw std::runtime_error("Unable to load assets script");
    }

}
