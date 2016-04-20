package com.gxengine.gx;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.Surface;

public class GActivity extends Activity implements GWindow.Delegate {

	public GActivity() {
		
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            Bundle bundle = ai.metaData;
            String libName = bundle.getString("android.app.lib_name");
            System.loadLibrary(libName);
        } catch (Exception e) {
            e.printStackTrace();
        }
		GJavaJAPI.InitActivity();
		GAndroid.MainActivity(this);
		
		_window=new GWindow(this,this);
		this.setContentView(_window);
	}

	@Override
	protected void onStart() {
		super.onStart();
		GJavaJAPI.AppStart();
	}

	@Override
	protected void onResume() {
		super.onResume();
		GJavaJAPI.AppResume();
		
		startTimer();
	}

	@Override
	protected void onPause() {
		super.onPause();
		stopTimer();
		
		GJavaJAPI.AppPause();
	}

	@Override
	protected void onStop() {
		super.onStop();
		GJavaJAPI.AppStop();
	}

	@Override
	protected void onDestroy() {
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
		int idx=event.getActionIndex();
		GJavaJAPI.MainWindowOnTouchEvent(event.getActionMasked(),
				event.getPointerId(idx), 
				event.getX(idx)*event.getXPrecision(), 
				event.getY(idx)*event.getYPrecision());
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
	
	private GWindow _window;

	private long _msPerFrame=1000L/30;
	private Handler _handler = new Handler( );
	private Runnable _runnable = new Runnable( ) {
		public void run ( ) {
			_handler.postDelayed(this,_msPerFrame);
			idle();
		}
	};
}
