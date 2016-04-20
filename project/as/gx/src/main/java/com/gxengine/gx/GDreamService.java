package com.gxengine.gx;

import android.annotation.SuppressLint;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.service.dreams.DreamService;
import android.view.MotionEvent;
import android.view.Surface;

@SuppressLint("NewApi")
public class GDreamService extends DreamService implements GWindow.Delegate {

	public GDreamService() {

	}

	@Override
	public void onCreate() {
		super.onCreate();
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
		GJavaJAPI.InitDaydream();
		GAndroid.MainDaydream(this);
	}

	@Override
	public void onAttachedToWindow() {
		super.onAttachedToWindow();
		
		_window=new GWindow(this,this);
		this.setContentView(_window);
	}

	@Override
	public void onDetachedFromWindow() {
		
		super.onDetachedFromWindow();
	}

	@Override
	public void onDreamingStarted() {
		super.onDreamingStarted();
		
		startTimer();
		GJavaJAPI.AppResume();
	}

	@Override
	public void onDreamingStopped() {
		super.onDreamingStopped();
		stopTimer();
		GJavaJAPI.AppPause();
	}

	@Override
	public void onDestroy() {
		GJavaJAPI.AppDestroy();
		super.onDestroy();
		
		int nPid = android.os.Process.myPid();
	    android.os.Process.killProcess(nPid);
	}
	
	@Override
	public void onLowMemory() {
		super.onLowMemory();
		GJavaJAPI.AppLowMemory();
	}

	@Override
	public void onWindowCreated(GWindow win, Surface surface) {
		GJavaJAPI.MainWindowHasCreated(surface);
	}
	
	@Override
	public void onWindowChanged(GWindow win, Surface surface, int width, int height) {
		GJavaJAPI.MainWindowHasChanged(surface, width, height);
	}
	
	@Override
	public void onWindowDestroyed(GWindow win, Surface surface) {
		GJavaJAPI.MainWindowHasDestroyed(surface);
	}
	
	@Override
	public void onWindowTouchEvent(GWindow win, MotionEvent event) {
		
	}
	
	private void startTimer() {
		_msPerFrame=1000L/ GJavaJAPI.AppSuggestFPS();
		_handler.postDelayed(_runnable,_msPerFrame);
	}
	private void stopTimer() {
		_handler.removeCallbacks(_runnable);
	}
	
	private void idle() {
		GJavaJAPI.AppIdle();
	}
	
	GWindow _window;
	
	private long _msPerFrame=1000L/30;
	private Handler _handler = new Handler( );
	private Runnable _runnable = new Runnable( ) {
		public void run ( ) {
			_handler.postDelayed(this,_msPerFrame);
			idle();
		}
	};
}
