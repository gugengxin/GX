package com.gxengine.gx;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.GX;

public class GActivity extends Activity implements GWindow.Delegate {

	public static final long IDLE_MS_PE_RFRAME=1000L/60;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
			throw new RuntimeException("Error getting application info", e);
        }
		GJavaJAPI.appCreate(GX.LaunchTypeActivity,this);
		GX.main(GX.LaunchTypeActivity);
		
		_window=new GWindow(this,this);
		this.setContentView(_window);
	}

	@Override
	protected void onStart() {
		super.onStart();
		GJavaJAPI.appStart();
	}

	@Override
	protected void onResume() {
		super.onResume();
		GJavaJAPI.appResume();
		
		startTimer();
	}

	@Override
	protected void onPause() {
		super.onPause();
		stopTimer();
		
		GJavaJAPI.appPause();
	}

	@Override
	protected void onStop() {
		super.onStop();
		GJavaJAPI.appStop();
	}

	@Override
	protected void onDestroy() {
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
		int idx=event.getActionIndex();
		GJavaJAPI.mainWindowOnTouchEvent(event.getActionMasked(),
				event.getPointerId(idx), 
				event.getX(idx)*event.getXPrecision(), 
				event.getY(idx)*event.getYPrecision());
	}

	
	private void startTimer() {
		_handler.postDelayed(_runnable,IDLE_MS_PE_RFRAME);
	}
	private void stopTimer() {
		_handler.removeCallbacks(_runnable);
	}
	
	private void idle() {
		GJavaJAPI.appIdle();
	}
	
	private GWindow _window;

	private Handler _handler = new Handler( );
	private Runnable _runnable = new Runnable( ) {
		public void run ( ) {
			_handler.postDelayed(this,IDLE_MS_PE_RFRAME);
			idle();
		}
	};
}
