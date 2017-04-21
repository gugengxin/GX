package com.gxengine.game;

import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.service.dreams.DreamService;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.core.GAndroidApp;

@SuppressLint("NewApi")
public class GAndroidDaydream extends DreamService implements GAndroidWindow.Delegate {

	public static void start(String gameClassName) {
		Intent intent=new Intent(GAndroidApp.shared(),GAndroidDaydream.class);
		if (gameClassName!=null) {
			Bundle bundle = new Bundle();
			bundle.putString(GAndroidActivity.KEY_GAME_CLASS_NAME, gameClassName);
			intent.putExtras(bundle);
		}
		GAndroidApp.shared().startService(intent);
	}

	public Bundle getMetaDataBundle() {
		try {
			ComponentName cn=new ComponentName(this, this.getClass());
			return getPackageManager().getServiceInfo(cn, PackageManager.GET_META_DATA).metaData;
		} catch (Exception e) {
			throw new RuntimeException("Error getMetaDataBundle", e);
		}
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.d(this.getClass().getSimpleName(),"onStartCommand");

        {
            Bundle bundle = intent.getExtras();
            if(bundle!=null) {
                _gameClassName = bundle.getString(GAndroidActivity.KEY_GAME_CLASS_NAME);
            }
        }

		return super.onStartCommand(intent, flags, startId);
	}

	@Override
	public void onCreate() {
		super.onCreate();
		Log.d(this.getClass().getSimpleName(),"onCreate");

		if (_gameClassName==null) {
			Bundle bundle = getMetaDataBundle();
			if(bundle!=null) {
				_gameClassName = bundle.getString(GAndroidActivity.KEY_GAME_CLASS_NAME);
			}
		}
		if (_gameClassName==null) {
			throw new RuntimeException("Error no gameClassName");
		}

		_window=new GAndroidWindow(this,this);
		this.setContentView(_window);
		_jniBridgeID=jniOnCreate();
	}

	@Override
	public void onAttachedToWindow() {
		super.onAttachedToWindow();
		Log.d(this.getClass().getSimpleName(),"onAttachedToWindow");

		jniOnAttachedToWindow(_jniBridgeID);
	}

	@Override
	public void onDreamingStarted() {
		super.onDreamingStarted();
		Log.d(this.getClass().getSimpleName(),"onDreamingStarted");

		jniOnDreamingStarted(_jniBridgeID);
	}

	@Override
	public void onDreamingStopped() {
		jniOnDreamingStopped(_jniBridgeID);

		Log.d(this.getClass().getSimpleName(),"onDreamingStopped");
		super.onDreamingStopped();
	}

	@Override
	public void onDetachedFromWindow() {
		jniOnDetachedFromWindow(_jniBridgeID);

		Log.d(this.getClass().getSimpleName(),"onDetachedFromWindow");
		super.onDetachedFromWindow();
	}

	@Override
	public void onDestroy() {
		jniOnDestroy(_jniBridgeID);

		Log.d(this.getClass().getSimpleName(),"onDestroy");
		super.onDestroy();
	}

	@Override
	public void onWindowCreated(GAndroidWindow win, Surface surface) {
		Log.d(this.getClass().getSimpleName(),"onWindowCreated");
		jniOnWindowCreated(_jniBridgeID,win,surface,_gameClassName);
	}
	
	@Override
	public void onWindowChanged(GAndroidWindow win, Surface surface, int width, int height) {
		Log.d(this.getClass().getSimpleName(),"onWindowChanged");
		jniOnWindowChanged(_jniBridgeID,win,surface,width,height);
	}
	
	@Override
	public void onWindowDestroyed(GAndroidWindow win, Surface surface) {
		jniOnWindowDestroyed(_jniBridgeID,win,surface);
		Log.d(this.getClass().getSimpleName(),"onWindowDestroyed");
	}
	
	@Override
	public void onWindowTouchEvent(GAndroidWindow win, MotionEvent event) {
		
	}

	private native long jniOnCreate();
	private native void jniOnAttachedToWindow(long bridgeID);
	private native void jniOnDreamingStarted(long bridgeID);
	private native void jniOnDreamingStopped(long bridgeID);
	private native void jniOnDetachedFromWindow(long bridgeID);
	private native void jniOnDestroy(long bridgeID);
	private native void jniOnWindowCreated(long bridgeID, GAndroidWindow win, Surface surface, String gameClassName);
	private native void jniOnWindowChanged(long bridgeID, GAndroidWindow win, Surface surface, int width, int height);
	private native void jniOnWindowDestroyed(long bridgeID, GAndroidWindow win, Surface surface);
	
	GAndroidWindow _window=null;
	private long _jniBridgeID=0L;
    private String _gameClassName=null;
}
