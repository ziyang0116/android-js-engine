package com.jsengine.hermes;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

@DoNotStrip
public class HermesRuntime extends JavaScriptRuntime {

    static {
        System.loadLibrary("hermes");
        System.loadLibrary("hermes-runtime");
    }

    public HermesRuntime() {
        super(initHybridDefaultConfig());
    }

    @Override
    public String getName() {
        return "HermesRuntime";
    }

    private static native HybridData initHybridDefaultConfig();

}
