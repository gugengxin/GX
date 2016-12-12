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

		_window=new GWindow(this,this);
		this.setContentView(_window);
		GAndroidJ.dreamServiceOnCreate(this);
	}

	@Override
	public void onAttachedToWindow() {
		super.onAttachedToWindow();
		Log.d(this.getClass().getSimpleName(),"onAttachedToWindow");

		GAndroidJ.dreamServiceOnAttachedToWindow(this);
	}

	@Override
	public void onDreamingStarted() {
		super.onDreamingStarted();
		Log.d(this.getClass().getSimpleName(),"onDreamingStarted");

		GAndroidJ.dreamServiceOnDreamingStarted(this);
	}

	@Override
	public void onDreamingStopped() {
		GAndroidJ.dreamServiceOnDreamingStopped(this);

		Log.d(this.getClass().getSimpleName(),"onDreamingStopped");
		super.onDreamingStopped();
	}

	@Override
	public void onDetachedFromWindow() {
		GAndroidJ.dreamServiceOnDetachedFromWindow(this);

		Log.d(this.getClass().getSimpleName(),"onDetachedFromWindow");
		super.onDetachedFromWindow();
	}

	@Override
	public void onDestroy() {
		GAndroidJ.dreamServiceOnDestroy(this);

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
	
	GWindow _window;
}
