package com.gxengine.core;

import android.app.Application;
import android.content.ComponentCallbacks;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;

import java.util.UUID;

/**
 * Created by GuGengxin on 2017/4/13.
 */

public class GAndroidApp extends Application {

    public static final String KEY_LIB_NAME="gx.lib.name";
    public static final String KEY_DELEGATE_CLASS_NAME="gx.core.app.delegate.name";

    public static final long IDLE_MS_PE_RFRAME = 1000L / 60;

    private static GAndroidApp INSTANCE;

    public static GAndroidApp shared() {
        return INSTANCE;
    }

    public float getDefaultWindowScale() {
        return getResources().getDisplayMetrics().density;
    }
    public String getCacheDirAbsolutePath() {
        return getCacheDir().getAbsolutePath();
    }

    public byte[] createUUID() {
        byte[] res=new byte[16];

        UUID uuid= UUID.randomUUID();

        long v=uuid.getMostSignificantBits();
        res[0]=(byte)(v&0xFF);
        res[1]=(byte)((v>>>1)&0xFF);
        res[2]=(byte)((v>>>2)&0xFF);
        res[3]=(byte)((v>>>3)&0xFF);
        res[4]=(byte)((v>>>4)&0xFF);
        res[5]=(byte)((v>>>5)&0xFF);
        res[6]=(byte)((v>>>6)&0xFF);
        res[7]=(byte)((v>>>7)&0xFF);
        v=uuid.getLeastSignificantBits();
        res[8+0]=(byte)((v)&0xFF);
        res[8+1]=(byte)((v>>>1)&0xFF);
        res[8+2]=(byte)((v>>>2)&0xFF);
        res[8+3]=(byte)((v>>>3)&0xFF);
        res[8+4]=(byte)((v>>>4)&0xFF);
        res[8+5]=(byte)((v>>>5)&0xFF);
        res[8+6]=(byte)((v>>>6)&0xFF);
        res[8+7]=(byte)((v>>>7)&0xFF);
        return res;
    }

    public Bundle getMetaDataBundle() {
        try {
            return getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA).metaData;
        } catch (Exception e) {
            throw new RuntimeException("Error getMetaDataBundle", e);
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
        INSTANCE = this;

        Bundle bundle = getMetaDataBundle();
        String libName = bundle.getString(KEY_LIB_NAME);
        String appDgeName=bundle.getString(KEY_DELEGATE_CLASS_NAME);

        System.loadLibrary(libName);
        jniOnCreate(getClassLoader());
        jniMain(appDgeName);
        startTimer();
    }

    @Override
    public void onTerminate() {
        jniOnTerminate();
        stopTimer();
        INSTANCE=null;
        super.onTerminate();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onLowMemory() {
        super.onLowMemory();
        jniOnLowMemory();
    }

    @Override
    public void onTrimMemory(int level) {
        super.onTrimMemory(level);
    }

    @Override
    public void registerComponentCallbacks(ComponentCallbacks callback) {
        super.registerComponentCallbacks(callback);
    }

    @Override
    public void unregisterComponentCallbacks(ComponentCallbacks callback) {
        super.unregisterComponentCallbacks(callback);
    }

    @Override
    public void registerActivityLifecycleCallbacks(ActivityLifecycleCallbacks callback) {
        super.registerActivityLifecycleCallbacks(callback);
    }

    @Override
    public void unregisterActivityLifecycleCallbacks(ActivityLifecycleCallbacks callback) {
        super.unregisterActivityLifecycleCallbacks(callback);
    }

    @Override
    public void registerOnProvideAssistDataListener(OnProvideAssistDataListener callback) {
        super.registerOnProvideAssistDataListener(callback);
    }

    @Override
    public void unregisterOnProvideAssistDataListener(OnProvideAssistDataListener callback) {
        super.unregisterOnProvideAssistDataListener(callback);
    }

    private native void jniOnCreate(ClassLoader classLoader);
    private native void jniMain(String appDgeName);
    private native void jniOnTerminate();
    private native void jniOnLowMemory();
    private native void jniIdle();


    private void startTimer() {
        _handler.postDelayed(_runnable, IDLE_MS_PE_RFRAME);
    }

    private void stopTimer() {
        _handler.removeCallbacks(_runnable);
    }

    private Handler _handler = new Handler();
    private Runnable _runnable = new Runnable() {
        public void run() {
            _handler.postDelayed(this, IDLE_MS_PE_RFRAME);
            jniIdle();
        }
    };
}
