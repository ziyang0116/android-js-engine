package com.jsengine;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public abstract class JavaScriptRuntime {

    @DoNotStrip
    private final HybridData mHybridData;

    protected JavaScriptRuntime(String libEnginePath, String libRuntimePath) {
        loadLibrary(libEnginePath, libRuntimePath);
        mHybridData = initHybridData();
    }

    public void close() {
        mHybridData.resetNative();
    }

    public abstract String getName();

    public abstract void loadLibrary(String libEnginePath, String libRuntimePath);

    public abstract HybridData initHybridData();
}
