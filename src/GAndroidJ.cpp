//
// Created by Gu Gengxin on 2016/12/10.
//

#include "GAndroidJ.h"
#if defined(GX_OS_ANDROID)

#include "GAndroid.h"
#include "GApplication.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    appOnCreate
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_appOnCreate
        (JNIEnv *env, jclass, jobject app, jobject classLoader)
{
    GAndroid::shared()->init(env,app,classLoader);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    appOnTerminate
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_appOnTerminate
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    appOnLowMemory
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_appOnLowMemory
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    appIdle
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_appIdle
        (JNIEnv *, jclass, jobject)
{
    GApplication::shared()->idle();
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnCreate
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnCreate
        (JNIEnv *, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnCreate(winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnReStart
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnReStart
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnStart
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnStart
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnResume
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnResume
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnPause
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnPause
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnStop
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnStop
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnDestroy
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnDestroy
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnCreate
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnCreate
        (JNIEnv *, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnCreate(winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnAttachedToWindow
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnAttachedToWindow
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDreamingStarted
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDreamingStarted
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDreamingStopped
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDreamingStopped
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDetachedFromWindow
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDetachedFromWindow
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDestroy
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDestroy
        (JNIEnv *, jclass, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnCreated
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnCreated
        (JNIEnv *, jclass, jobject, jobject, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnChanged
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnChanged
        (JNIEnv *, jclass, jobject, jobject, jint, jint, jobject)
{

}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnDestroyed
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnDestroyed
        (JNIEnv *, jclass, jobject, jobject, jobject)
{

}

#ifdef __cplusplus
}
#endif


#endif
