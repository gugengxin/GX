//
// Created by Gengxin Gu on 2017/4/13.
//

#include "GAndroidApp.h"
#if defined(GX_OS_ANDROID)

#include "GApplication.h"

GAndroidApp* GAndroidApp::shared()
{
    static GAndroidApp g_Obj;
    return &g_Obj;
}

GAndroidApp::GAndroidApp()
{
    m_JNIObject=NULL;
}

GAndroidApp::~GAndroidApp()
{

}

void GAndroidApp::init(JNIEnv *env, jobject ardApp, jobject classLoader)
{
    GJNI::init(env,classLoader);
    GJNI::Caller::init(env, "com/gxengine/core/GAndroidApp");
    m_JNIObject=env->NewGlobalRef(ardApp);
    GX_JNI_CALLER_METHOD_INIT(env,getDefaultWindowScale,"()F");
    GX_JNI_CALLER_METHOD_INIT(env,getCacheDirAbsolutePath,"()Ljava/lang/String;");
    GX_JNI_CALLER_METHOD_INIT(env,getPackageCodePath,"()Ljava/lang/String;");
    GX_JNI_CALLER_METHOD_INIT(env,createUUID,"()[B");
}

void GAndroidApp::uninit(JNIEnv *env, jobject ardApp)
{
    env->DeleteGlobalRef(m_JNIObject);
    GJNI::Caller::uninit(env);
    GJNI::uninit(env);
}

float GAndroidApp::getDefaultWindowScale(JNIEnv *jniEnv)
{
    return callFloatMethod(jniEnv,m_JNIObject,GX_JNI_CALLER_METHOD_GET(getDefaultWindowScale));
}

float GAndroidApp::getDefaultWindowScale()
{
    EnvHolder env;
    return getDefaultWindowScale(env.get());
}

GString *GAndroidApp::getCacheDirAbsolutePath(JNIEnv *jniEnv)
{
    GString *res = NULL;
    jstring str = (jstring) callObjectMethod(jniEnv,m_JNIObject,GX_JNI_CALLER_METHOD_GET(getCacheDirAbsolutePath));
    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GString::autoAlloc();
        res->setChars(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}

GString *GAndroidApp::getCacheDirAbsolutePath()
{
    EnvHolder env;
    return getCacheDirAbsolutePath(env.get());
}

GString *GAndroidApp::getPackageCodePath(JNIEnv *jniEnv)
{
    GString *res = NULL;
    jstring str = (jstring) callObjectMethod(jniEnv,m_JNIObject,GX_JNI_CALLER_METHOD_GET(getPackageCodePath));
    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GString::autoAlloc();
        res->setChars(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}

GString *GAndroidApp::getPackageCodePath()
{
    EnvHolder env;
    return getPackageCodePath(env.get());
}

void GAndroidApp::createUUID(JNIEnv *jniEnv, guint8 *uuidOut)
{
    jbyteArray barr = (jbyteArray) callObjectMethod(jniEnv, m_JNIObject,GX_JNI_CALLER_METHOD_GET(createUUID));

    jbyte *ba = jniEnv->GetByteArrayElements(barr, JNI_FALSE);

    memcpy(uuidOut, ba, 16);

    jniEnv->ReleaseByteArrayElements(barr, ba, 0);

    jniEnv->DeleteLocalRef(barr);
}

void GAndroidApp::createUUID(guint8 *uuidOut)
{
    EnvHolder env;
    createUUID(env.get(),uuidOut);
}

/////////////////////////// JNI //////////////////////////////

JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniOnCreate
        (JNIEnv *env, jobject sender, jobject classLoader)
{
    GAndroidApp::shared()->init(env,sender,classLoader);
}

JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniMain
        (JNIEnv *env, jobject sender, jstring appDgeName)
{
    const char *cstr = env->GetStringUTFChars(appDgeName, NULL);
    GApplication::main(0,NULL,cstr);
    env->ReleaseStringUTFChars(appDgeName, cstr);
}

JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniOnTerminate
        (JNIEnv *env, jobject sender)
{
    GApplication::shared()->eventWillTerminate();
    GAndroidApp::shared()->uninit(env,sender);
}

JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniOnLowMemory
        (JNIEnv *, jobject)
{
    GApplication::shared()->eventReceivedMemoryWarning();
}

JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniIdle
        (JNIEnv *, jobject)
{
    GApplication::shared()->idle();
}


#endif