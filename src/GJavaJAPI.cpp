//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaJAPI.h"
#if defined(GX_OS_ANDROID)

#include "GApplication.h"
#include "GJavaAPI.h"
#include <android/native_window_jni.h>

class GJavaJAPI {
public:
    static void mainWindowHasCreated(JNIEnv *env,jobject surface) {
//        ANativeWindow* nw=ANativeWindow_fromSurface(env, surface);
//        GApplication::shared()->AndroidWindowCreated(nw);
//        ANativeWindow_release(nw);
    }
    static void mainWindowHasChanged() {
//        GApplication::shared()->AndroidWindowChanged();
    }
    static void mainWindowHasDestroyed() {
//        GApplication::shared()->AndroidWindowDestroyed();
    }
    static void mainWindowOnTouchEvent(jint action,jint pointerId,jfloat x,jfloat y) {
//        GApplication::shared()->AndroidWindowOnTouchEvent(action,pointerId,x,y);
    }
    static void appIdle() {

    }
    static void appStart() {
//        GApplication::shared()->AndroidAppStart();
    }
    static void appResume() {
//        GApplication::shared()->AndroidAppResume();
    }
    static void appPause() {
//        GApplication::shared()->AndroidAppPause();
    }
    static void appStop() {
//        GApplication::shared()->AndroidAppStop();
    }
    static void appDestroy() {
//        GApplication::shared()->AndroidAppDestroy();
    }
    static void appLowMemory() {
//        GApplication::shared()->AndroidAppLowMemory();
    }
};

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_initActivity
        (JNIEnv *, jclass, jobject activity)
{
    GX::JavaInitActivity(activity);
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_initDaydream
        (JNIEnv *, jclass, jobject daydream)
{
    GX::JavaInitDaydream(daydream);
}



JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasCreated
        (JNIEnv *env, jclass, jobject surface)
{
    GJavaJAPI::mainWindowHasCreated(env,surface);
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasChanged
        (JNIEnv *, jclass, jobject, jint, jint)
{
    GJavaJAPI::mainWindowHasChanged();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasDestroyed
        (JNIEnv *, jclass, jobject)
{
    GJavaJAPI::mainWindowHasDestroyed();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowOnTouchEvent
        (JNIEnv *, jclass, jint action, jint pointerId, jfloat x, jfloat y)
{
    GJavaJAPI::mainWindowOnTouchEvent(action,pointerId,x,y);
}



JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appIdle
        (JNIEnv *, jclass)
{
    GJavaJAPI::appIdle();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appStart
        (JNIEnv *, jclass)
{
    GJavaJAPI::appStart();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appResume
        (JNIEnv *, jclass)
{
    GJavaJAPI::appResume();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appPause
        (JNIEnv *, jclass)
{
    GJavaJAPI::appPause();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appStop
        (JNIEnv *, jclass)
{
    GJavaJAPI::appStop();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appDestroy
        (JNIEnv *, jclass)
{
    GJavaJAPI::appDestroy();
}
JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appLowMemory
        (JNIEnv *, jclass)
{
    GJavaJAPI::appLowMemory();
}

#ifdef __cplusplus
}
#endif

#endif
