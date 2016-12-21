//
// Created by Gengxin Gu on 2016/12/9.
//

#include "GAndroid.h"
#if defined(GX_OS_ANDROID)

#include "GApplication.h"

GAndroid* GAndroid::shared()
{
    static GAndroid g_Obj;
    return &g_Obj;
}

GAndroid::GAndroid()
{
    m_AndroidApp=NULL;
}

GAndroid::~GAndroid()
{

}

void GAndroid::init(JNIEnv *env, jobject ardApp, jobject classLoader)
{
    GJNI::init(env,classLoader);
    m_AndroidApp=ardApp;
}

void GAndroid::uninit(JNIEnv *env, jobject ardApp)
{
    GApplication::shared()->eventWillTerminate();
    m_AndroidApp=NULL;
    GJNI::uninit(env);
}



#endif