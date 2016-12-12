//
// Created by Gengxin Gu on 2016/12/9.
//

#include "GAndroid.h"
#if defined(GX_OS_ANDROID)


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




#endif