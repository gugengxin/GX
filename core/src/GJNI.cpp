//
// Created by Gengxin Gu on 2016/12/9.
//

#include "GJNI.h"
#if defined(GX_OS_ANDROID)
#include "GLog.h"

static GJNI* g_Obj=NULL;

GJNI* GJNI::shared()
{
    return g_Obj;
}

GJNI::GJNI()
{
    GX_ASSERT(g_Obj==NULL);
    g_Obj=this;

    m_VM=NULL;
    m_CLInst=NULL;
    m_CLClass=NULL;
    m_CLLoadClassMd=NULL;
}

GJNI::~GJNI()
{

}

void GJNI::init(JNIEnv *env, jobject classLoader)
{
    env->GetJavaVM(&m_VM);

    jclass clClass = env->FindClass("java/lang/ClassLoader");
    jmethodID findClass = env->GetMethodID(clClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    m_CLInst=env->NewGlobalRef(classLoader);
    m_CLClass=(jclass)env->NewGlobalRef(clClass);
    m_CLLoadClassMd=findClass;

    env->DeleteLocalRef(clClass);
}

void GJNI::uninit(JNIEnv *env)
{
    env->DeleteGlobalRef(m_CLClass);
    env->DeleteGlobalRef(m_CLInst);
}


JNIEnv *GJNI::attachEnv(bool *needDetach)
{
    JNIEnv *env;
    jint res = m_VM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (JNI_EDETACHED == res) {
        if (JNI_OK == m_VM->AttachCurrentThread(&env, NULL)) {
            if (needDetach)
                (*needDetach) = true;
        }
        else {
            GX_ASSERT(0);
        }
    }
    else if (JNI_OK == res) {
        if (needDetach)
            (*needDetach) = false;
    }
    else {
        GX_ASSERT(0);
    }
    return env;
}

void GJNI::detachEnv()
{
    m_VM->DetachCurrentThread();
}

jclass GJNI::findClass(JNIEnv *jniEnv, const char *name)
{
    char cTemp[256];
    int i = 0;
    while (true) {
        if (name[i] == '/') {
            cTemp[i] = '.';
        }
        else {
            cTemp[i] = name[i];
            if (!name[i]) {
                break;
            }
        }
        i++;
    }
    jstring strClassName = jniEnv->NewStringUTF(cTemp);
    jclass res = (jclass) jniEnv->CallObjectMethod(m_CLInst,m_CLLoadClassMd, strClassName);
    jniEnv->DeleteLocalRef(strClassName);
    return res;
}




GJNI::Caller::Caller()
{
    m_Class=NULL;
}
GJNI::Caller::~Caller()
{

}

void GJNI::Caller::init(JNIEnv* jniEnv,const char* className)
{
    jclass tmp=shared()->findClass(jniEnv,className);
    GX_ASSERT(tmp);
    m_Class=(jclass)jniEnv->NewGlobalRef(tmp);
    jniEnv->DeleteLocalRef(tmp);
}

void GJNI::Caller::uninit(JNIEnv* jniEnv)
{
    jniEnv->DeleteGlobalRef(m_Class);
}

jmethodID GJNI::Caller::getMethod(JNIEnv* jniEnv,const char* name,const char* sig)
{
    return jniEnv->GetMethodID(m_Class,name,sig);
}

jmethodID GJNI::Caller::getStaticMethod(JNIEnv* jniEnv,const char* name,const char* sig)
{
    return jniEnv->GetStaticMethodID(m_Class,name,sig);
}

void GJNI::Caller::callStaticVoidMethod(JNIEnv* jniEnv,jmethodID method,...)
{
    va_list args;
    va_start(args, method);
    jniEnv->CallStaticVoidMethodV(m_Class, method, args);
    va_end(args);
}
jobject GJNI::Caller::callStaticObjectMethod(JNIEnv* jniEnv,jmethodID method,...)
{
    va_list args;
    jobject result;
    va_start(args, method);
    result = jniEnv->CallStaticObjectMethodV(m_Class, method, args);
    va_end(args);
    return result;
}
jbyte GJNI::Caller::callStaticByteMethod(JNIEnv* jniEnv,jmethodID method,...)
{
    va_list args;
    jbyte result;
    va_start(args, method);
    result = jniEnv->CallStaticByteMethodV(m_Class, method, args);
    va_end(args);
    return result;
}
jfloat GJNI::Caller::callStaticFloatMethod(JNIEnv* jniEnv,jmethodID method,...)
{
    va_list args;
    jfloat result;
    va_start(args, method);
    result = jniEnv->CallStaticFloatMethodV(m_Class, method, args);
    va_end(args);
    return result;
}


void GJNI::Caller::callVoidMethod(JNIEnv* jniEnv,jobject obj,jmethodID method,...)
{
    va_list args;
    va_start(args, method);
    jniEnv->CallVoidMethodV(obj, method, args);
    va_end(args);
}
jobject GJNI::Caller::callObjectMethod(JNIEnv* jniEnv,jobject obj,jmethodID method,...)
{
    va_list args;
    jobject result;
    va_start(args, method);
    result = jniEnv->CallObjectMethodV(obj, method, args);
    va_end(args);
    return result;
}
jint GJNI::Caller::callIntMethod(JNIEnv* jniEnv,jobject obj,jmethodID method,...)
{
    va_list args;
    int result;
    va_start(args, method);
    result = jniEnv->CallIntMethodV(obj,method,args);
    va_end(args);
    return result;
}


/*
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    GX_LOG_P1(PrioDEBUG, "JNI_OnLoad", "%p", vm);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

#ifdef __cplusplus
}
#endif

}
#endif
//*/


#endif


