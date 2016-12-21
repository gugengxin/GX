//
// Created by Gengxin Gu on 2016/12/9.
//

#ifndef AS_GANDROID_H
#define AS_GANDROID_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include "GJNI.h"
#include "com_gxengine_gx_GAndroidJ.h"

class GAndroid : public GJNI {
    friend void Java_com_gxengine_gx_GAndroidJ_appInit(JNIEnv*, jclass, jobject, jobject);
    friend void Java_com_gxengine_gx_GAndroidJ_appUninit(JNIEnv*, jclass, jobject);
public:
    static GAndroid* shared();
private:
    GAndroid();
    virtual ~GAndroid();

    void init(JNIEnv *env, jobject ardApp, jobject classLoader);
    void uninit(JNIEnv *env, jobject ardApp);
public:



private:
    jobject m_AndroidApp;
};


#endif

#endif //AS_GANDROID_H
