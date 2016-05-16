//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaJAPI.h"
#if defined(GX_OS_ANDROID)

#include "GApplication.h"
#include "GJavaAPI.h"
#include <android/native_window_jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appCreate
        (JNIEnv *, jclass, jint lt, jobject mi) {
    GX::JavaInit(GX_CAST_S(GX::JavaLaunchType,lt),mi);
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appStart
        (JNIEnv *, jclass) {
    GApplication::shared()->eventStart();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appResume
        (JNIEnv *, jclass) {
    GApplication::shared()->eventResume();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appIdle
        (JNIEnv *, jclass) {
    GApplication::shared()->idle();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appPause
        (JNIEnv *, jclass) {
    GApplication::shared()->eventPause();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appStop
        (JNIEnv *, jclass) {
    GApplication::shared()->eventStop();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appDestroy
        (JNIEnv *, jclass) {
    GApplication::shared()->eventDestroy();
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_appLowMemory
        (JNIEnv *, jclass) {

}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasCreated
        (JNIEnv *env, jclass, jobject surface) {
    static bool first=true;
    if(first) {
        first=false;
        ANativeWindow* nw=ANativeWindow_fromSurface(env, surface);
        GApplication::shared()->setCanCreateWindow(nw);
        ANativeWindow_release(nw);
    }
    else {

    }
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasChanged
        (JNIEnv *, jclass, jobject, jint, jint) {
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowHasDestroyed
        (JNIEnv *, jclass, jobject) {
}

JNIEXPORT void JNICALL Java_com_gxengine_gx_GJavaJAPI_mainWindowOnTouchEvent
        (JNIEnv *, jclass, jint, jint, jfloat, jfloat) {
}

#ifdef __cplusplus
}
#endif

#endif
