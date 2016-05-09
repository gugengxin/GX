//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaAPI.h"

#if defined(GX_OS_ANDROID)

#include <android/asset_manager_jni.h>
#include "GLog.h"

namespace GX {

    class _JavaClassLoader {
    public:
        _JavaClassLoader() :
                instance(NULL),
                classId(NULL),
                loadClassMId(NULL) { }

        ~_JavaClassLoader() { }

        jobject instance;
        jclass classId;
        jmethodID loadClassMId;
    };

    class _JavaData {
    public:
        _JavaData() :
                vm(NULL),
                launchType(JavaLaunchTypeDefault),
                assetManager(NULL),
                classLoader(),
                mainInstance(NULL) { }

        ~_JavaData() { }

        JavaVM *vm;
        JavaLaunchType launchType;
        AAssetManager *assetManager;
        _JavaClassLoader classLoader;
        jobject mainInstance;
    };


    static _JavaData g_JavaData;

    JavaVM *JavaGetVM() {
        return g_JavaData.vm;
    }

    JavaLaunchType JavaGetLaunchType() {
        return g_JavaData.launchType;
    }

    static void _JavaInit(JNIEnv *env, const char *aiyClassName) {
        jclass activityClass = env->FindClass(aiyClassName);
        jmethodID getClassLoader = env->GetMethodID(activityClass, "getClassLoader",
                                                    "()Ljava/lang/ClassLoader;");
        jobject cls = env->CallObjectMethod(g_JavaData.mainInstance, getClassLoader);
        jclass classLoader = env->FindClass("java/lang/ClassLoader");
        jmethodID findClass = env->GetMethodID(classLoader, "loadClass",
                                               "(Ljava/lang/String;)Ljava/lang/Class;");

        g_JavaData.classLoader.instance = env->NewGlobalRef(cls);
        g_JavaData.classLoader.classId = (jclass) env->NewGlobalRef(classLoader);
        g_JavaData.classLoader.loadClassMId = findClass;

        {
            jmethodID getAsset = env->GetMethodID(activityClass, "getAssets",
                                                  "()Landroid/content/res/AssetManager;");
            jobject am = env->CallObjectMethod(g_JavaData.mainInstance, getAsset);
            g_JavaData.assetManager = AAssetManager_fromJava(env, am);
            env->DeleteLocalRef(am);
        }

        env->DeleteLocalRef(classLoader);
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(activityClass);
    }

    void JavaInit(JavaLaunchType launchType,jobject mainInstance)
    {
        GX_LOG_P1(PrioDEBUG, "JavaInit", "%p", mainInstance);
        g_JavaData.launchType = JavaLaunchTypeActivity;
        GJavaJNIEnvAutoPtr jniEnv;
        g_JavaData.mainInstance = jniEnv.get()->NewGlobalRef(mainInstance);

        if(launchType==JavaLaunchTypeActivity) {
            _JavaInit(jniEnv.get(), "android/app/Activity");
        }
        else {
            _JavaInit(jniEnv.get(), "android/service/dreams/DreamService");
        }
    }

    bool JavaMainInstanceIsActivity() {
        return g_JavaData.launchType == JavaLaunchTypeActivity;
    }

    bool JavaMainInstanceIsDreamService() {
        return g_JavaData.launchType == JavaLaunchTypeDaydream;
    }

    jobject JavaGetMainInstance() {
        return g_JavaData.mainInstance;
    }

    AAssetManager *JavaGetAssetManager() {
        return g_JavaData.assetManager;
    }

    JNIEnv *JavaGetEnv(bool *needDetach) {
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

    void JavaDetachEnv() {
        g_JavaData.vm->DetachCurrentThread();
    }

    jclass JavaFindClass(JNIEnv *jniEnv, const char *name) {
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
}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    GX::g_JavaData.vm = vm;
    GX_LOG_P1(PrioDEBUG, "JNI_OnLoad", "%p", vm);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

#ifdef __cplusplus
}
#endif

}
#endif