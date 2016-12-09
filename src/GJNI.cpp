//
// Created by Gengxin Gu on 2016/12/9.
//

#include "GJNI.h"
#if defined(GX_OS_ANDROID)
#include "GLog.h"

GJNI* GJNI::shared()
{
    static GJNI g_Obj;
    return &g_Obj;
}




JNIEnv *GJNI::attachEnv(bool *needDetach)
{
    JNIEnv *env;
    jint res = g_JavaData.vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (JNI_EDETACHED == res) {
        if (JNI_OK == g_JavaData.vm->AttachCurrentThread(&env, NULL)) {
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
    g_JavaData.vm->DetachCurrentThread();
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
    jclass res = (jclass) jniEnv->CallObjectMethod(g_JavaData.classLoader.instance,
                                                   g_JavaData.classLoader.loadClassMId, strClassName);
    jniEnv->DeleteLocalRef(strClassName);
    return res;
}


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_JavaData.vm = vm;
    GX_LOG_P1(PrioDEBUG, "JNI_OnLoad", "%p", vm);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

#ifdef __cplusplus
}
#endif

}
#endif


#endif


