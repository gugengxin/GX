package com.gxengine.gx;

public class GJavaJAPI {
	public static native void initActivity(Object activity);
	public static native void initDaydream(Object daydream);
	
	public static native void mainWindowHasCreated(Object surface);
	public static native void mainWindowHasChanged(Object surface,int wdith,int height);
	public static native void mainWindowHasDestroyed(Object surface);
	public static native void mainWindowOnTouchEvent(int action,int pointerId,float x,float y);
	
	public static native void appIdle();
	public static native void appStart();
	public static native void appResume();
	public static native void appPause();
	public static native void appStop();
	public static native void appDestroy();
	public static native void appLowMemory();
}
