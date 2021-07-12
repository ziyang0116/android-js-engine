package com.jsengine.hermes;

import android.text.TextUtils;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

@DoNotStrip
public class HermesRuntime extends JavaScriptRuntime {

    public HermesRuntime() {
        super(null, null);
    }

    public HermesRuntime(String libEnginePath, String libRuntimePath) {
        super(libEnginePath, libRuntimePath);
    }

    @Override
    public String getName() {
        return "HermesRuntime";
    }

    @Override
    public void loadLibrary(String libEnginePath, String libRuntimePath) {
        if (TextUtils.isEmpty(libEnginePath)) {
            System.loadLibrary("hermes");
        } else {
            System.load(libEnginePath);
        }
        if (TextUtils.isEmpty(libRuntimePath)) {
            System.loadLibrary("hermes-runtime");
        } else {
            System.load(libRuntimePath);
        }

    }

    @Override
    public HybridData initHybridData() {
        return initHybridDefaultConfig();
    }

    private static native HybridData initHybridDefaultConfig();

}
