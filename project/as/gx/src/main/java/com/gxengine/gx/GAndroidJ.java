package com.gxengine.gx;

/**
 * Created by GuGengxin on 2016/12/10.
 */

public class GAndroidJ {
    public static native void appOnCreate(Object app,Object classLoader);
    public static native void appOnTerminate(Object app);
    public static native void appIdle(Object app);

    public static native void activityOnCreate(Object activity);
    public static native void activityOnStart(Object activity);
    public static native void activityOnResume(Object activity);
    public static native void activityOnPause(Object activity);
    public static native void activityOnStop(Object activity);
    public static native void activityOnDestroy(Object activity);

    public static native void dreamServiceOnCreate(Object dreamService);
    public static native void dreamServiceOnAttachedToWindow(Object dreamService);
    public static native void dreamServiceOnDreamingStarted(Object dreamService);
    public static native void dreamServiceOnDreamingStopped(Object dreamService);
    public static native void dreamServiceOnDetachedFromWindow(Object dreamService);
    public static native void dreamServiceOnDestroy(Object dreamService);

    public static native void windowOnCreated(Object win, Object surface, Object winHolder);
    public static native void windowOnChanged(Object win, Object surface, int width, int height, Object winHolder);
    public static native void windowOnDestroyed(Object win, Object surface, Object winHolder);
}
