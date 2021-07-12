package com.jsengine.v8;

import android.os.Build;
import android.os.StrictMode;
import android.text.TextUtils;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.jsengine.JavaScriptRuntime;

import org.w3c.dom.Text;

import java.util.TimeZone;

@DoNotStrip
public class V8Runtime extends JavaScriptRuntime {

    public V8Runtime() {
        super(null, null);
    }

    public V8Runtime(String libEnginePath, String libRuntimePath) {
        super(libEnginePath, libRuntimePath);
    }

    @Override
    public String getName() {
        return "V8Runtime";
    }

    @Override
    public void loadLibrary(String libEnginePath, String libRuntimePath) {
        if (TextUtils.isEmpty(libEnginePath)) {
            System.loadLibrary("v8android");
        } else {
            System.load(libEnginePath);
        }
        if (TextUtils.isEmpty(libRuntimePath)) {
            System.loadLibrary("v8-runtime");
        } else {
            System.load(libRuntimePath);
        }
    }

    @Override
    public HybridData initHybridData() {
        return initHybrid(getTimezoneId());
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
