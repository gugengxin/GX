//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaAPI.h"
#if defined(GX_OS_ANDROID)
#include <android/asset_manager_jni.h>
#include "GLog.h"

namespace GX {

    static JavaVM* v_VM=NULL;
    static struct {
        jobject 	instance;
        jclass  	classId;
        jmethodID 	loadClassMId;
    } gav_ClassLoader;
    static jobject v_MainInstance=NULL;
    static JavaLaunchType v_LaunchType=JavaLaunchTypeNative;
    static AAssetManager* v_AssetManager=NULL;

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
    {
        v_VM=vm;
        GX_LOG_P1(PrioDEBUG,"JNI_OnLoad","%p",vm);
        return JNI_VERSION_1_6;
    }
    JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved)
    {

    }

    JavaVM* JavaGetVM()
    {
        return v_VM;
    }

    JavaLaunchType JavaGetLaunchType()
    {
        return v_LaunchType;
    }

    void JavaSetLaunchType(JavaLaunchType v)
    {
        v_LaunchType=v;
    }

    static void _JavaInit(JNIEnv* env,const char* aiyClassName)
    {
        jclass activityClass=env->FindClass(aiyClassName);
        jmethodID getClassLoader=env->GetMethodID(activityClass,"getClassLoader","()Ljava/lang/ClassLoader;");
        jobject cls=env->CallObjectMethod(v_MainInstance,getClassLoader);
        jclass classLoader=env->FindClass("java/lang/ClassLoader");
        jmethodID findClass=env->GetMethodID(classLoader,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");

        gav_ClassLoader.instance=env->NewGlobalRef(cls);
        gav_ClassLoader.classId=(jclass)env->NewGlobalRef(classLoader);
        gav_ClassLoader.loadClassMId=findClass;

        if(!v_AssetManager) {
            jmethodID getAsset=env->GetMethodID(activityClass,"getAssets","()Landroid/content/res/AssetManager;");
            jobject am=env->CallObjectMethod(v_MainInstance,getAsset);
            v_AssetManager=AAssetManager_fromJava(env,am);
            env->DeleteLocalRef(am);
        }

        env->DeleteLocalRef(classLoader);
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(activityClass);
    }

    void JavaInitNative(ANativeActivity* nativaActivity)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitNative","%p",nativaActivity->vm);
        v_VM=nativaActivity->vm;
        GJavaJNIEnvAutoPtr jniEnv;

        v_MainInstance=nativaActivity->clazz;
        v_AssetManager=nativaActivity->assetManager;
        _JavaInit(jniEnv.Get(),"android/app/NativeActivity");
    }

    void JavaInitActivity(jobject activity)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitActivity","%p",activity);
        GJavaJNIEnvAutoPtr jniEnv;

        v_MainInstance=jniEnv.Get()->NewGlobalRef(activity);
        v_AssetManager=NULL;
        _JavaInit(jniEnv.Get(),"android/app/Activity");
    }

    void JavaInitDaydream(jobject daydream)
    {
        GX_LOG_P1(PrioDEBUG,"JavaInitDaydream","%p",daydream);
        GJavaJNIEnvAutoPtr jniEnv;

        v_MainInstance=jniEnv.Get()->NewGlobalRef(daydream);
        v_AssetManager=NULL;
        _JavaInit(jniEnv.Get(),"android/service/dreams/DreamService");
    }

    bool JavaMainInstanceIsActivity()
    {
        return v_LaunchType==JavaLaunchTypeNative || v_LaunchType==JavaLaunchTypeActivity;
    }
    bool JavaMainInstanceIsDreamService()
    {
        return v_LaunchType==JavaLaunchTypeDaydream;
    }

    jobject JavaGetMainInstance()
    {
        return v_MainInstance;
    }

    AAssetManager* JavaGetAssetManager()
    {
        return v_AssetManager;
    }

    JNIEnv* JavaGetEnv(bool* needDetach)
    {
        JNIEnv* env;
        jint res=v_VM->GetEnv((void**) &env, JNI_VERSION_1_6);
        if(JNI_EDETACHED==res) {
            if(JNI_OK==v_VM->AttachCurrentThread(&env, NULL)) {
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
        v_VM->DetachCurrentThread();
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
        jclass res=(jclass)jniEnv->CallObjectMethod(gav_ClassLoader.instance,gav_ClassLoader.loadClassMId,strClassName);
        jniEnv->DeleteLocalRef(strClassName);
        return res;
    }
}

#endif