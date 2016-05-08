//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaAPI.h"
#if defined(GX_OS_ANDROID)
#include <android/asset_manager_jni.h>
#include "GLog.h"

namespace GX {

    static JavaVM* g_VM=NULL;
    static struct {
        jobject 	instance;
        jclass  	classId;
        jmethodID 	loadClassMId;
    } g_ClassLoader;
    static jobject g_MainInstance=NULL;
    static JavaLaunchType g_LaunchType=JavaLaunchTypeNative;
    static AAssetManager* g_AssetManager=NULL;

    JavaVM* JavaGetVM()
    {
        return g_VM;
    }

    JavaLaunchType JavaGetLaunchType()
    {
        return g_LaunchType;
    }

    static void _JavaInit(JNIEnv* env,const char* aiyClassName)
    {
        jclass activityClass=env->FindClass(aiyClassName);
        jmethodID getClassLoader=env->GetMethodID(activityClass,"getClassLoader","()Ljava/lang/ClassLoader;");
        jobject cls=env->CallObjectMethod(g_MainInstance,getClassLoader);
        jclass classLoader=env->FindClass("java/lang/ClassLoader");
        jmethodID findClass=env->GetMethodID(classLoader,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");

        g_ClassLoader.instance=env->NewGlobalRef(cls);
        g_ClassLoader.classId=(jclass)env->NewGlobalRef(classLoader);
        g_ClassLoader.loadClassMId=findClass;

        if(!g_AssetManager) {
            jmethodID getAsset=env->GetMethodID(activityClass,"getAssets","()Landroid/content/res/AssetManager;");
            jobject am=env->CallObjectMethod(g_MainInstance,getAsset);
            g_AssetManager=AAssetManager_fromJava(env,am);
            env->DeleteLocalRef(am);
        }

        env->DeleteLocalRef(classLoader);
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(activityClass);
    }

    void JavaInitNative(ANativeActivity* nativaActivity)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitNative","%p",nativaActivity->vm);
        g_LaunchType=JavaLaunchTypeNative;
        g_VM=nativaActivity->vm;
        GJavaJNIEnvAutoPtr jniEnv;

        g_MainInstance=nativaActivity->clazz;
        g_AssetManager=nativaActivity->assetManager;
        _JavaInit(jniEnv.get(),"android/app/NativeActivity");
    }

    void JavaInitActivity(jobject activity)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitActivity","%p",activity);
        g_LaunchType=JavaLaunchTypeActivity;
        GJavaJNIEnvAutoPtr jniEnv;

        g_MainInstance=jniEnv.get()->NewGlobalRef(activity);
        g_AssetManager=NULL;
        _JavaInit(jniEnv.get(),"android/app/Activity");
    }

    void JavaInitDaydream(jobject daydream)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitDaydream","%p",daydream);
        g_LaunchType=JavaLaunchTypeDaydream;
        GJavaJNIEnvAutoPtr jniEnv;

        g_MainInstance=jniEnv.get()->NewGlobalRef(daydream);
        g_AssetManager=NULL;
        _JavaInit(jniEnv.get(),"android/service/dreams/DreamService");
    }

    bool JavaMainInstanceIsActivity()
    {
        return g_LaunchType==JavaLaunchTypeNative || g_LaunchType==JavaLaunchTypeActivity;
    }
    bool JavaMainInstanceIsDreamService()
    {
        return g_LaunchType==JavaLaunchTypeDaydream;
    }

    jobject JavaGetMainInstance()
    {
        return g_MainInstance;
    }

    AAssetManager* JavaGetAssetManager()
    {
        return g_AssetManager;
    }

    JNIEnv* JavaGetEnv(bool* needDetach)
    {
        JNIEnv* env;
        jint res=g_VM->GetEnv((void**) &env, JNI_VERSION_1_6);
        if(JNI_EDETACHED==res) {
            if(JNI_OK==g_VM->AttachCurrentThread(&env, NULL)) {
                if(needDetach)
                    (*needDetach)=true;
            }
            else {
                GX_ASSERT(0);
            }
        }
        else if(JNI_OK==res) {
            if(needDetach)
                (*needDetach)=false;
        }
        else {
            GX_ASSERT(0);
        }
        return env;
    }

    void JavaDetachEnv()
    {
        g_VM->DetachCurrentThread();
    }

    jclass JavaFindClass(JNIEnv* jniEnv,const char* name)
    {
        char cTemp[256];
        int i=0;
        while(true) {
            if(name[i]=='/') {
                cTemp[i]='.';
            }
            else {
                cTemp[i]=name[i];
                if(!name[i]) {
                    break;
                }
            }
            i++;
        }
        jstring strClassName=jniEnv->NewStringUTF(cTemp);
        jclass res=(jclass)jniEnv->CallObjectMethod(g_ClassLoader.instance,g_ClassLoader.loadClassMId,strClassName);
        jniEnv->DeleteLocalRef(strClassName);
        return res;
    }
}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    GX::g_VM = vm;
    GX_LOG_P1(PrioDEBUG, "JNI_OnLoad", "%p", vm);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

#ifdef __cplusplus
}
#endif

}
#endif