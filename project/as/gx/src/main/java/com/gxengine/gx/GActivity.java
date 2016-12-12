package com.gxengine.gx;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.GX;

public class GActivity extends Activity implements GWindow.Delegate {

	public static final long IDLE_MS_PE_RFRAME=1000L/60;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(this.getClass().getSimpleName(),"onCreate");

		_window=new GWindow(this,this);
		this.setContentView(_window);
		GAndroidJ.activityOnCreate(this);
	}

	@Override
	protected void onStart() {
		super.onStart();
        Log.d(this.getClass().getSimpleName(),"onStart");
		GAndroidJ.activityOnStart(this);
	}

	@Override
	protected void onResume() {
		super.onResume();
        Log.d(this.getClass().getSimpleName(),"onResume");
		GAndroidJ.activityOnResume(this);
	}

	@Override
	protected void onPause() {
		GAndroidJ.activityOnPause(this);

		Log.d(this.getClass().getSimpleName(),"onPause");
		super.onPause();
	}

	@Override
	protected void onStop() {
		GAndroidJ.activityOnStop(this);

		Log.d(this.getClass().getSimpleName(),"onStop");
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		GAndroidJ.activityOnDestroy(this);

        Log.d(this.getClass().getSimpleName(),"onDestroy");
		super.onDestroy();
	}
	
	@Override
	public void onWindowCreated(GWindow win, Surface surface) {
        Log.d(this.getClass().getSimpleName(),"onWindowCreated");
		GAndroidJ.windowOnCreated(win,surface,this);
	}
	
	@Override
	public void onWindowChanged(GWindow win, Surface surface, int width, int height) {
        Log.d(this.getClass().getSimpleName(),"onWindowChanged");
		GAndroidJ.windowOnChanged(win,surface,width,height,this);
	}
	
	@Override
	public void onWindowDestroyed(GWindow win, Surface surface) {
		GAndroidJ.windowOnDestroyed(win,surface,this);
        Log.d(this.getClass().getSimpleName(),"onWindowDestroyed");
	}
	
	@Override
	public void onWindowTouchEvent(GWindow win, MotionEvent event) {

	}

	private GWindow _window;
}
