package com.gxengine.gx;

public class GJavaJAPI {
	public static native void appCreate(int launchType,Object mainInstance);
	public static native void appStart();
	public static native void appResume();
	public static native void appIdle();
	public static native void appPause();
	public static native void appStop();
	public static native void appDestroy();
	public static native void appLowMemory();

	public static native void mainWindowHasCreated(Object surface);
	public static native void mainWindowHasChanged(Object surface,int width,int height);
	public static native void mainWindowHasDestroyed(Object surface);
	public static native void mainWindowOnTouchEvent(int action,int pointerId,float x,float y);
}
