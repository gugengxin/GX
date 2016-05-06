package com.gxengine.gx;

import android.annotation.SuppressLint;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.service.dreams.DreamService;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.GX;

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
		GJavaJAPI.initDaydream(this);
		GX.main(GX.LaunchTypeDaydream);
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
		GJavaJAPI.appResume();
	}

	@Override
	public void onDreamingStopped() {
		super.onDreamingStopped();
		stopTimer();
		GJavaJAPI.appPause();
	}

	@Override
	public void onDestroy() {
		GJavaJAPI.appDestroy();
		super.onDestroy();
		
		int nPid = android.os.Process.myPid();
	    android.os.Process.killProcess(nPid);
	}
	
	@Override
	public void onLowMemory() {
		super.onLowMemory();
		GJavaJAPI.appLowMemory();
	}

	@Override
	public void onWindowCreated(GWindow win, Surface surface) {
		GJavaJAPI.mainWindowHasCreated(surface);
	}
	
	@Override
	public void onWindowChanged(GWindow win, Surface surface, int width, int height) {
		GJavaJAPI.mainWindowHasChanged(surface, width, height);
	}
	
	@Override
	public void onWindowDestroyed(GWindow win, Surface surface) {
		GJavaJAPI.mainWindowHasDestroyed(surface);
	}
	
	@Override
	public void onWindowTouchEvent(GWindow win, MotionEvent event) {
		
	}
	
	private void startTimer() {
		_handler.postDelayed(_runnable,_msPerFrame);
	}
	private void stopTimer() {
		_handler.removeCallbacks(_runnable);
	}
	
	private void idle() {
		GJavaJAPI.appIdle();
	}
	
	GWindow _window;
	
	private long _msPerFrame=1000L/60;
	private Handler _handler = new Handler( );
	private Runnable _runnable = new Runnable( ) {
		public void run ( ) {
			_handler.postDelayed(this,_msPerFrame);
			idle();
		}
	};
}
