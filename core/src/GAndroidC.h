//
// Created by Gu Gengxin on 2016/12/10.
//

#ifndef AS_GANDROIDC_H
#define AS_GANDROIDC_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include "GJNI.h"
#include "GString.h"

class GAndroidC : public  GJNI::Caller {
public:
    static GAndroidC* shared();
private:
    GAndroidC();
    ~GAndroidC();
    virtual void init(JNIEnv* jniEnv,const char* className);
public:
    float appGetDefaultWindowScale(JNIEnv* jniEnv);
    float appGetDefaultWindowScale();
    GString* appGetCacheDir(JNIEnv* jniEnv);
    GString* appGetCacheDir();
    GString* appGetPackageCodePath(JNIEnv* jniEnv);
    GString* appGetPackageCodePath();
    void appStartActivity(JNIEnv* jniEnv);
    void appStartActivity();
    void UUIDCreate(JNIEnv* jniEnv,guint8* uuidOut);
    void UUIDCreate(guint8* uuidOut);

private:
    jmethodID m_MappGetDefaultWindowScale;
    jmethodID m_MappGetCacheDir;
    jmethodID m_MappGetPackageCodePath;
    jmethodID m_MappStartActivity;
    jmethodID m_MUUIDCreate;
};




#endif

#endif //AS_GANDROIDC_H
