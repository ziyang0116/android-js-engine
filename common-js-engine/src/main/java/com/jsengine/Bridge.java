package com.jsengine;

import android.content.res.AssetManager;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public class Bridge {

    private static final String TAG = "javascript-lib";

    static {
        System.loadLibrary("javascript-lib");
    }

    // C++ parts
    private final HybridData mHybridData;


    public Bridge() {
        mHybridData = initHybrid();
    }

    public void initialize(JavaScriptRuntime runtime) {
        initializeBridge(runtime);
    }

    public void loadScriptFromString(String jsString) {
        jniLoadScriptFromString(jsString);
    }

    public Object callJSFunctionSync(String function, Object args) {
        return jniCallJSFunctionSync(function, args);
    }

    public void callJSFunction(String function, Object args, JSCallback callback) {
        jniCallJSFunction(function, args, callback);
    }

    public void loadScriptFromAssets(AssetManager assetManager, String assetName) {
        jniLoadScriptFromAssets(assetManager, assetName);
    }

    private static native HybridData initHybrid();

    native void initializeBridge(JavaScriptRuntime javaScriptRuntime);

    native void jniLoadScriptFromAssets(AssetManager assetManager, String assetName);

    native void jniLoadScriptFromString(String jsString);

    native void setGlobalVariable(String propName, String jsonValue);

    native Object jniCallJSFunctionSync(String functionName, Object args);

    native void jniCallJSFunction(String functionName, Object args, JSCallback callback);
}

