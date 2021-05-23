package com.jsengine;

import com.facebook.proguard.annotations.DoNotStrip;

@DoNotStrip
public abstract class JSCallback {

    public abstract void invoke(Object object);
}
