package com.jsengine;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public abstract class JavaScriptRuntime {

    @DoNotStrip
    private final HybridData mHybridData;

    protected JavaScriptRuntime(HybridData hybridData) {
        mHybridData = hybridData;
    }

    public void close() {
        mHybridData.resetNative();
    }

    public abstract String getName();
}
