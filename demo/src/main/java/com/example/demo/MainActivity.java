package com.example.demo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.jsengine.Bridge;
import com.jsengine.JSCallback;
import com.jsengine.hermes.HermesRuntime;
import com.jsengine.jsc.JSCRuntime;
import com.jsengine.v8.V8Runtime;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "js-engine";

    ViewGroup hermesViewGroup;
    ViewGroup jscViewGroup;
    ViewGroup v8ViewGroup;

    Bridge hermesBridge;
    Bridge jscBridge;
    Bridge v8Bridge;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        hermesViewGroup = findViewById(R.id.hermes);
        jscViewGroup = findViewById(R.id.jsc);
        v8ViewGroup = findViewById(R.id.v8);
        hermesBridge = new Bridge();
        hermesBridge.initialize(new HermesRuntime());
        control(hermesViewGroup, hermesBridge, "hermes");
        jscBridge = new Bridge();
        jscBridge.initialize(new JSCRuntime());
        control(jscViewGroup, jscBridge, "jsc");
        v8Bridge = new Bridge();
        v8Bridge.initialize(new V8Runtime());
        control(v8ViewGroup, v8Bridge, "v8");
    }

    private void control(ViewGroup viewGroup, Bridge bridge, String txt) {
        TextView tv = viewGroup.findViewById(R.id.groupText);
        tv.setText(txt);
        Button loadScriptFromStringBtn = viewGroup.findViewById(R.id.loadScriptFromString);
        loadScriptFromStringBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String js = loadJSTemplateFromAssets();
                bridge.loadScriptFromString(js);
            }
        });
        Button loadScriptFromAssetsBtn = viewGroup.findViewById(R.id.loadScriptFromAssets);
        loadScriptFromAssetsBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bridge.loadScriptFromAssets(getAssets(), "assets://app.js");
            }
        });
        Button callJSFunctionSyncBtn = viewGroup.findViewById(R.id.callJSFunctionSync);
        callJSFunctionSyncBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                List<Object> args = new ArrayList<>();
                args.add("arg1");
                args.add("arg2");
                Object result = bridge.callJSFunctionSync("__myfunctionSync", args);
                if (result instanceof Map) {
                    Log.d(TAG, ((Map) result).keySet().toString());
                }
            }
        });
        Button callJSFunctionBtn = viewGroup.findViewById(R.id.callJSFunction);
        callJSFunctionBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                List<String> args = new ArrayList<>();
                args.add("1");
                args.add("2");
                bridge.callJSFunction("__myfunction", args, new JSCallback() {
                    @Override
                    public void invoke(Object object) {
                        if (object instanceof String) {
                            Log.d(TAG, object.toString());
                        } else if (object instanceof Map) {
                            Log.d(TAG, ((Map) object).keySet().toString());
                        }
                    }
                });
            }
        });

    }

    private String loadJSTemplateFromAssets() {
        String js = null;
        try {
            InputStream is = getAssets().open("app.js");
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            js = new String(buffer, "UTF-8");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return js;
    }
}