//
// Created by Gengxin Gu on 16/5/5.
//

#ifndef AS_GJAVAAPI_H
#define AS_GJAVAAPI_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include <jni.h>
#include <native_app_glue/android_native_app_glue.h>

namespace GX {

    JavaVM* JavaGetVM();

    typedef enum _JavaLaunchType {
        JavaLaunchTypeNative,
        JavaLaunchTypeActivity,
        JavaLaunchTypeDaydream,
    } JavaLaunchType;

    JavaLaunchType GXJavaGetLaunchType();
    void JavaInitNative(ANativeActivity* nativaActivity);
    void JavaInitActivity(jobject activity);
    void JavaInitDaydream(jobject daydream);

    bool JavaMainInstanceIsActivity();
    bool JavaMainInstanceIsDreamService();
    jobject JavaGetMainInstance();
    AAssetManager* JavaGetAssetManager();
    JNIEnv* JavaGetEnv(bool* needDetach);
    void JavaDetachEnv();


    jclass JavaFindClass(JNIEnv* jniEnv,const char* name);
}

class GJavaJNIEnvAutoPtr {
public:
    GJavaJNIEnvAutoPtr() {
        m_Env=GX::JavaGetEnv(&m_NeedDetach);
    }

    virtual ~GJavaJNIEnvAutoPtr() {
        if(m_NeedDetach) {
            GX::JavaDetachEnv();
        }
    }

    JNIEnv* Get() {
        return m_Env;
    }

private:
    JNIEnv* m_Env;
    bool m_NeedDetach;
};


#endif


#endif //AS_GJAVAAPI_H
