package com.gxengine.game;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;

import com.gxengine.core.GAndroidApp;

public class GAndroidActivity extends Activity implements GAndroidWindow.Delegate {

    public static final String KEY_GAME_CLASS_NAME="gx.game.name";

	public static void start(String gameClassName) {
        Intent intent=new Intent(GAndroidApp.shared(),GAndroidActivity.class);
        if (gameClassName!=null) {
			Bundle bundle = new Bundle();
			bundle.putString(KEY_GAME_CLASS_NAME, gameClassName);
			intent.putExtras(bundle);
		}
        GAndroidApp.shared().startActivity(intent);
	}

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

        {
            Bundle bundle = this.getIntent().getExtras();
            if(bundle!=null) {
                _gameClassName = bundle.getString(KEY_GAME_CLASS_NAME);
            }
        }
        if (_gameClassName==null) {
            Bundle bundle = getMetaDataBundle();
            if(bundle!=null) {
                _gameClassName = bundle.getString(KEY_GAME_CLASS_NAME);
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
	private native void jniOnRestart(long bridgeID);
	private native void jniOnStart(long bridgeID);
	private native void jniOnResume(long bridgeID);
	private native void jniOnPause(long bridgeID);
	private native void jniOnStop(long bridgeID);
	private native void jniOnDestroy(long bridgeID);
	private native void jniOnWindowCreated(long bridgeID, GAndroidWindow win, Surface surface, String gameClassName);
	private native void jniOnWindowChanged(long bridgeID, GAndroidWindow win, Surface surface, int width, int height);
	private native void jniOnWindowDestroyed(long bridgeID, GAndroidWindow win, Surface surface);


	private GAndroidWindow _window=null;
	private long _jniBridgeID=0L;
	private String _gameClassName=null;
}
