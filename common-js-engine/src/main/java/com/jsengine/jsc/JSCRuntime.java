package com.jsengine.jsc;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

@DoNotStrip
public class JSCRuntime extends JavaScriptRuntime {

    static {
        System.loadLibrary("jsc");
        System.loadLibrary("jsc-runtime");
    }

    public JSCRuntime() {
        super(initHybridDefaultConfig());
    }

    @Override
    public String getName() {
        return "JSCRuntime";
    }

    private static native HybridData initHybridDefaultConfig();

}
