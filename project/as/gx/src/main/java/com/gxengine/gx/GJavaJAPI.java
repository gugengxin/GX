package com.gxengine.gx;

public class GJavaJAPI {
	public static native void InitActivity();
	public static native void InitDaydream();
	
	public static native void MainWindowHasCreated(Object surface);
	public static native void MainWindowHasChanged(Object surface,int wdith,int height);
	public static native void MainWindowHasDestroyed(Object surface);
	public static native void MainWindowOnTouchEvent(int action,int pointerId,float x,float y);
	
	public static native int AppSuggestFPS();
	
	public static native void AppIdle();
	public static native void AppStart();
	public static native void AppResume();
	public static native void AppPause();
	public static native void AppStop();
	public static native void AppDestroy();
	public static native void AppLowMemory();
}
