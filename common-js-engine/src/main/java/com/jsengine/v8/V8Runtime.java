package com.jsengine.v8;

import android.os.Build;
import android.os.StrictMode;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

import java.util.TimeZone;

@DoNotStrip
public class V8Runtime extends JavaScriptRuntime {

    static {
        System.loadLibrary("v8android");
        System.loadLibrary("v8-runtime");
    }

    public V8Runtime() {
        super(initHybrid(getTimezoneId()));
    }

    @Override
    public String getName() {
        return "V8Runtime";
    }

    private static native HybridData initHybrid(String timezoneId);

    private static String getTimezoneId() {
        if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.N) {
            final StrictMode.ThreadPolicy oldPolicy =
                    StrictMode.allowThreadDiskReads();
            final String timezoneId = TimeZone.getDefault().getID();
            StrictMode.setThreadPolicy(oldPolicy);
            return timezoneId;
        } else {
            final String timezoneId = TimeZone.getDefault().getID();
            return timezoneId;
        }
    }

}
