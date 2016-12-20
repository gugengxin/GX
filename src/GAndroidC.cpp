//
// Created by Gu Gengxin on 2016/12/10.
//

#include "GAndroidC.h"
#if defined(GX_OS_ANDROID)

#define M_METHOD_ID(name) m_M##name

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
#define M_METHOD(name) M_METHOD_ID(name)=NULL
    M_METHOD(appGetDefaultWindowScale);
    M_METHOD(appGetCacheDir);
    M_METHOD(appGetPackageCodePath);
    M_METHOD(appStartActivity);
    M_METHOD(UUIDCreate);
#undef M_METHOD
}

GAndroidC::~GAndroidC()
{

}



void GAndroidC::init(JNIEnv* jniEnv,const char* className)
{
    GJNI::Caller::init(jniEnv,className);

#define M_METHOD_INIT(name,sign) M_METHOD_ID(name)=getMethod(jniEnv,#name,sign,true)
    M_METHOD_INIT(appGetDefaultWindowScale,"()F");
    M_METHOD_INIT(appGetCacheDir,"()Ljava/lang/String;");
    M_METHOD_INIT(appGetPackageCodePath,"()Ljava/lang/String;");
    M_METHOD_INIT(appStartActivity,"()V");
    M_METHOD_INIT(UUIDCreate,"()[B");
#undef M_METHOD_INIT
}


float GAndroidC::appGetDefaultWindowScale(JNIEnv* jniEnv)
{
    return callStaticFloatMethod(jniEnv,M_METHOD_ID(appGetDefaultWindowScale));
}
float GAndroidC::appGetDefaultWindowScale()
{
    GJNI::EnvHolder env;
    return appGetDefaultWindowScale(env.get());
}

GPath* GAndroidC::appGetCacheDir(JNIEnv* jniEnv)
{
    GPath *res = NULL;
    jstring str = (jstring) callStaticObjectMethod(jniEnv,M_METHOD_ID(appGetCacheDir));
    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GPath::autoAlloc();
        res->set(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}
GPath* GAndroidC::appGetCacheDir()
{
    GJNI::EnvHolder env;
    return appGetCacheDir(env.get());
}

GPath* GAndroidC::appGetPackageCodePath(JNIEnv* jniEnv)
{
    GPath *res = NULL;
    jstring str = (jstring) callStaticObjectMethod(jniEnv,M_METHOD_ID(appGetPackageCodePath));
    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GPath::autoAlloc();
        res->set(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}
GPath* GAndroidC::appGetPackageCodePath()
{
    GJNI::EnvHolder env;
    return appGetPackageCodePath(env.get());
}

void GAndroidC::appStartActivity(JNIEnv* jniEnv)
{
    callStaticVoidMethod(jniEnv,M_METHOD_ID(appStartActivity));
}

void GAndroidC::appStartActivity()
{
    GJNI::EnvHolder env;
    appStartActivity(env.get());
}

void GAndroidC::UUIDCreate(JNIEnv* jniEnv,guint8* uuidOut)
{
    jbyteArray barr = (jbyteArray) callStaticObjectMethod(jniEnv, M_METHOD_ID(UUIDCreate));

    jbyte *ba = jniEnv->GetByteArrayElements(barr, JNI_FALSE);

    memcpy(uuidOut, ba, 16);

    jniEnv->ReleaseByteArrayElements(barr, ba, 0);

    jniEnv->DeleteLocalRef(barr);
}
void GAndroidC::UUIDCreate(guint8* uuidOut)
{
    GJNI::EnvHolder env;
    UUIDCreate(env.get(),uuidOut);
}

#endif