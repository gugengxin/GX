package com.gxengine.gx;

import android.annotation.SuppressLint;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.service.dreams.DreamService;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.GX;

@SuppressLint("NewApi")
public class GDreamService extends DreamService implements GWindow.Delegate {

	@Override
	public void onCreate() {
		super.onCreate();
		Log.d(this.getClass().getSimpleName(),"onCreate");
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
		GJavaJAPI.appCreate(GX.LaunchTypeDaydream,this);
		GX.main(GX.LaunchTypeDaydream);
	}

	@Override
	public void onAttachedToWindow() {
		super.onAttachedToWindow();
		Log.d(this.getClass().getSimpleName(),"onAttachedToWindow");

		_window=new GWindow(this,this);
		this.setContentView(_window);
	}

	@Override
	public void onDetachedFromWindow() {

		Log.d(this.getClass().getSimpleName(),"onDetachedFromWindow");
		super.onDetachedFromWindow();
	}

	@Override
	public void onDreamingStarted() {
		super.onDreamingStarted();

		Log.d(this.getClass().getSimpleName(),"onDreamingStarted");
		startTimer();
		GJavaJAPI.appResume();
	}

	@Override
	public void onDreamingStopped() {
		super.onDreamingStopped();
		Log.d(this.getClass().getSimpleName(),"onDreamingStopped");
		stopTimer();
		GJavaJAPI.appPause();
	}

	@Override
	public void onDestroy() {
		Log.d(this.getClass().getSimpleName(),"onDestroy");
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
		Log.d(this.getClass().getSimpleName(),"onWindowCreated");
		GJavaJAPI.mainWindowHasCreated(surface);
	}
	
	@Override
	public void onWindowChanged(GWindow win, Surface surface, int width, int height) {
		Log.d(this.getClass().getSimpleName(),"onWindowChanged");
		GJavaJAPI.mainWindowHasChanged(surface, width, height);
	}
	
	@Override
	public void onWindowDestroyed(GWindow win, Surface surface) {
		Log.d(this.getClass().getSimpleName(),"onWindowDestroyed");
		GJavaJAPI.mainWindowHasDestroyed(surface);
	}
	
	@Override
	public void onWindowTouchEvent(GWindow win, MotionEvent event) {
		
	}
	
	private void startTimer() {
		_handler.postDelayed(_runnable,GActivity.IDLE_MS_PE_RFRAME);
	}
	private void stopTimer() {
		_handler.removeCallbacks(_runnable);
	}
	
	private void idle() {
		GJavaJAPI.appIdle();
	}
	
	GWindow _window;
	
	private Handler _handler = new Handler( );
	private Runnable _runnable = new Runnable( ) {
		public void run ( ) {
			_handler.postDelayed(this,GActivity.IDLE_MS_PE_RFRAME);
			idle();
		}
	};
}
