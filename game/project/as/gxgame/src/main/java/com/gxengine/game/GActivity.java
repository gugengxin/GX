package com.gxengine.game;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;

public class GActivity extends Activity implements GWindow.Delegate {

	public Bundle getMetaDataBundle() {
		try {
			return getPackageManager().getActivityInfo(getComponentName(),
					PackageManager.GET_META_DATA).metaData;
		} catch (Exception e) {
			throw new RuntimeException("Error getMetaDataBundle", e);
		}
	}


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(this.getClass().getSimpleName(),"onCreate");

		_window=new GWindow(this,this);
		this.setContentView(_window);




		_jniBridgeID=jniOnCreate();
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.d(this.getClass().getSimpleName(),"onRestart");
		jniOnRestart(_jniBridgeID);
	}

	@Override
	protected void onStart() {
		super.onStart();
        Log.d(this.getClass().getSimpleName(),"onStart");
		jniOnStart(_jniBridgeID);
	}



	@Override
	protected void onResume() {
		super.onResume();
        Log.d(this.getClass().getSimpleName(),"onResume");
		jniOnResume(_jniBridgeID);
	}

	@Override
	protected void onPause() {
		jniOnPause(_jniBridgeID);
		Log.d(this.getClass().getSimpleName(),"onPause");
		super.onPause();
	}

	@Override
	protected void onStop() {
		jniOnStop(_jniBridgeID);
		Log.d(this.getClass().getSimpleName(),"onStop");
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		jniOnDestroy(_jniBridgeID);
        Log.d(this.getClass().getSimpleName(),"onDestroy");
		super.onDestroy();
	}
	
	@Override
	public void onWindowCreated(GWindow win, Surface surface) {
        Log.d(this.getClass().getSimpleName(),"onWindowCreated");
		jniOnWindowCreated(_jniBridgeID,win,surface);
	}
	
	@Override
	public void onWindowChanged(GWindow win, Surface surface, int width, int height) {
        Log.d(this.getClass().getSimpleName(),"onWindowChanged");
		jniOnWindowChanged(_jniBridgeID,win,surface,width,height);
	}
	
	@Override
	public void onWindowDestroyed(GWindow win, Surface surface) {
		jniOnWindowDestroyed(_jniBridgeID,win,surface);
        Log.d(this.getClass().getSimpleName(),"onWindowDestroyed");
	}
	
	@Override
	public void onWindowTouchEvent(GWindow win, MotionEvent event) {

	}

	private native long jniOnCreate();
	private native void jniOnRestart(long bridgeID);
	private native void jniOnStart(long bridgeID);
	private native void jniOnResume(long bridgeID);
	private native void jniOnPause(long bridgeID);
	private native void jniOnStop(long bridgeID);
	private native void jniOnDestroy(long bridgeID);
	private native void jniOnWindowCreated(long bridgeID,GWindow win,Surface surface);
	private native void jniOnWindowChanged(long bridgeID,GWindow win,Surface surface,int width, int height);
	private native void jniOnWindowDestroyed(long bridgeID,GWindow win,Surface surface);


	private GWindow _window;
	private long _jniBridgeID;
}
