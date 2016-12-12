//
// Created by Gu Gengxin on 2016/12/10.
//

#include "GAndroidC.h"
#if defined(GX_OS_ANDROID)


GAndroidC* GAndroidC::shared()
{
    static GAndroidC g_Obj;
    if (!g_Obj.getClass()) {
        GJNI::EnvHolder env;
        g_Obj.init(env.get(),"com/gxengine/gx/GAndroidC");
    }
    return &g_Obj;
}

GAndroidC::GAndroidC()
{

}

GAndroidC::~GAndroidC()
{

}

void GAndroidC::init(JNIEnv* jniEnv,const char* className)
{
    GJNI::Caller::init(jniEnv,className);



}






#endif