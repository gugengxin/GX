package com.gxengine.gx;

import android.app.Application;
import android.content.ComponentCallbacks;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;

/**
 * Created by GuGengxin on 2016/12/8.
 */

public class GApplication extends Application {

    public static final long IDLE_MS_PE_RFRAME=1000L/60;

    private static GApplication INSTANCE;
    public static GApplication shared() {
        return INSTANCE;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        INSTANCE=this;

        try {
            Bundle bundle = getApplicationInfo().metaData;
            String libName = bundle.getString("gx.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            throw new RuntimeException("Error getting application info", e);
        }



        startTimer();
    }

    @Override
    public void onTerminate() {
        stopTimer();
        super.onTerminate();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onLowMemory() {
        super.onLowMemory();
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



    private void startTimer() {
        _handler.postDelayed(_runnable,IDLE_MS_PE_RFRAME);
    }
    private void stopTimer() {
        _handler.removeCallbacks(_runnable);
    }

    private void idle() {

    }

    private Handler _handler = new Handler( );
    private Runnable _runnable = new Runnable( ) {
        public void run ( ) {
            _handler.postDelayed(this,IDLE_MS_PE_RFRAME);
            idle();
        }
    };
}
