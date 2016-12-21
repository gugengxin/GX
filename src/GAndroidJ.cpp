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
        (JNIEnv *env, jclass, jobject app)
{
    GAndroid::shared()->uninit(env,app);
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
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnCreate(env,winHolder,GApplication::_WinHolderType_Activity);
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
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnStart(env,winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnResume
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnResume
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnResume(env,winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnPause
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnPause
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnPause(env,winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnStop
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnStop
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnStop(env,winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    activityOnDestroy
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_activityOnDestroy
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnDestroy(env,winHolder,GApplication::_WinHolderType_Activity);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnCreate
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnCreate
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnCreate(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnAttachedToWindow
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnAttachedToWindow
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnStart(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDreamingStarted
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDreamingStarted
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnResume(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDreamingStopped
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDreamingStopped
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnPause(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDetachedFromWindow
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDetachedFromWindow
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnStop(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    dreamServiceOnDestroy
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_dreamServiceOnDestroy
        (JNIEnv *env, jclass, jobject winHolder)
{
    GApplication::shared()->winHolderOnDestroy(env,winHolder,GApplication::_WinHolderType_DreamService);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnCreated
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnCreated
        (JNIEnv *env, jclass, jobject win, jobject surface, jobject winHolder)
{
    GApplication::shared()->winOnCreated(env,win,surface,winHolder);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnChanged
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnChanged
        (JNIEnv *env, jclass, jobject win, jobject surface, jint width, jint height, jobject winHolder)
{
    GApplication::shared()->winOnChanged(env,win,surface,width,height,winHolder);
}

/*
 * Class:     com_gxengine_gx_GAndroidJ
 * Method:    windowOnDestroyed
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_gxengine_gx_GAndroidJ_windowOnDestroyed
        (JNIEnv *env, jclass, jobject win, jobject surface, jobject winHolder)
{
    GApplication::shared()->winOnDestroyed(env,win,surface,winHolder);
}

#ifdef __cplusplus
}
#endif


#endif
