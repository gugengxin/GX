//
// Created by Gengxin Gu on 16/5/5.
//

#ifndef AS_GJAVAAPI_H
#define AS_GJAVAAPI_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include <jni.h>
#include <android/asset_manager_jni.h>

namespace GX {

    JavaVM* JavaGetVM();

    typedef enum _JavaLaunchType {
        JavaLaunchTypeActivity,
        JavaLaunchTypeDaydream,

        JavaLaunchTypeDefault=JavaLaunchTypeActivity,
    } JavaLaunchType;

    JavaLaunchType JavaGetLaunchType();
    void JavaInit(JavaLaunchType launchType,jobject mainInstance);

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

    JNIEnv* get() {
        return m_Env;
    }

private:
    JNIEnv* m_Env;
    bool m_NeedDetach;
};


#endif


#endif //AS_GJAVAAPI_H
