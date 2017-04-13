//
// Created by Gengxin Gu on 2017/4/13.
//

#ifndef AS_GANDROIDAPP_H
#define AS_GANDROIDAPP_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include "GJNI.h"
#include "GString.h"
#include "com_gxengine_core_GAndroidApp.h"

//Android Main Entrance
//JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniMain(JNIEnv *, jobject);


class GAndroidApp : public GJNI, public GJNI::Caller {
    friend void Java_com_gxengine_core_GAndroidApp_jniOnCreate(JNIEnv *, jobject, jobject);
    friend void Java_com_gxengine_core_GAndroidApp_jniOnTerminate(JNIEnv *, jobject);
public:
    static GAndroidApp* shared();
private:
    GAndroidApp();
    virtual ~GAndroidApp();

    void init(JNIEnv *env, jobject ardApp, jobject classLoader);
    void uninit(JNIEnv *env, jobject ardApp);
public:
    float getDefaultWindowScale(JNIEnv* jniEnv);
    float getDefaultWindowScale();
    GString* getCacheDirAbsolutePath(JNIEnv* jniEnv);
    GString* getCacheDirAbsolutePath();
    GString* getPackageCodePath(JNIEnv* jniEnv);
    GString* getPackageCodePath();
    void createUUID(JNIEnv* jniEnv,guint8* uuidOut);
    void createUUID(guint8* uuidOut);


private:
    jobject m_JNIObject;
private:
    GX_JNI_CALLER_METHOD(getDefaultWindowScale);
    GX_JNI_CALLER_METHOD(getCacheDirAbsolutePath);
    GX_JNI_CALLER_METHOD(getPackageCodePath);
    GX_JNI_CALLER_METHOD(createUUID);
};


#endif

#endif //AS_GANDROIDAPP_H
