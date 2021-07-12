package com.jsengine.jsc;

import android.text.TextUtils;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

@DoNotStrip
public class JSCRuntime extends JavaScriptRuntime {

    public JSCRuntime(String libEnginePath, String libRuntimePath) {
        super(libEnginePath, libRuntimePath);
    }

    public JSCRuntime(){
        super(null, null);
    }

    @Override
    public String getName() {
        return "JSCRuntime";
    }

    @Override
    public void loadLibrary(String libEnginePath, String libRuntimePath) {
        if (TextUtils.isEmpty(libEnginePath)) {
            System.loadLibrary("jsc");
        } else {
            System.load(libEnginePath);
        }
        if (TextUtils.isEmpty(libRuntimePath)) {
            System.loadLibrary("jsc-runtime");
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
