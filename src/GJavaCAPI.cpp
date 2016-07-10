//
// Created by Gengxin Gu on 16/5/5.
//

#include "GJavaCAPI.h"

#if defined(GX_OS_ANDROID)

typedef enum _JavaCAPIM {
    APIM_AppGetDefaultWindowScaleActivity,
    APIM_AppGetDefaultWindowScaleDreamService,
    APIM_AppGetCacheDir,
    APIM_AppGetPackageCodePath,
    APIM_AppTerminate,
    APIM_UUIDCreate,

    APIMCount,
} JavaCAPIM;


GJavaCAPI *GJavaCAPI::shared() {
    static GJavaCAPI g_Cls;

    if (g_Cls.getClass() == NULL) {
        GJavaJNIEnvAutoPtr jniEnv;

        g_Cls.setClass(jniEnv.get(), "com/gxengine/gx/GJavaCAPI");

        g_Cls.setMethod(jniEnv.get(),
                        APIM_AppGetDefaultWindowScaleActivity,
                        "appGetDefaultWindowScale",
                        "(Landroid/app/Activity;)F",
                        true);
        g_Cls.setMethod(jniEnv.get(),
                        APIM_AppGetDefaultWindowScaleDreamService,
                        "appGetDefaultWindowScale",
                        "(Landroid/service/dreams/DreamService;)F",
                        true);
        g_Cls.setMethod(jniEnv.get(), APIM_AppGetCacheDir,
                        "appGetCacheDir", "(Landroid/content/ContextWrapper;)Ljava/lang/String;",
                        true);
        g_Cls.setMethod(jniEnv.get(), APIM_AppGetPackageCodePath,
                        "appGetPackageCodePath",
                        "(Landroid/content/ContextWrapper;)Ljava/lang/String;", true);
        g_Cls.setMethod(jniEnv.get(), APIM_AppTerminate,
                        "appTerminate", "(Landroid/app/Activity;)V", true);

        g_Cls.setMethod(jniEnv.get(), APIM_UUIDCreate, "UUIDCreate", "()[B", true);
    }

    return &g_Cls;
}

float GJavaCAPI::appGetDefaultWindowScale(JNIEnv *jniEnv) {
    if (GX::JavaMainInstanceIsActivity()) {
        return callStaticFloatMethod(jniEnv, (int) APIM_AppGetDefaultWindowScaleActivity,
                                     GX::JavaGetMainInstance());
    }
    return callStaticFloatMethod(jniEnv, (int) APIM_AppGetDefaultWindowScaleDreamService,
                                 GX::JavaGetMainInstance());
}

GPath *GJavaCAPI::appGetCacheDir(JNIEnv *jniEnv) {
    GPath *res = NULL;
    jstring str = (jstring) callStaticObjectMethod(jniEnv,
                                                   APIM_AppGetCacheDir,
                                                   GX::JavaGetMainInstance());

    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GPath::autoAlloc();
        res->set(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}

GPath *GJavaCAPI::appGetPackageCodePath(JNIEnv *jniEnv) {
    GPath *res = NULL;
    jstring str = (jstring) callStaticObjectMethod(jniEnv,
                                                   APIM_AppGetPackageCodePath,
                                                   GX::JavaGetMainInstance());

    const char *cstr = jniEnv->GetStringUTFChars(str, NULL);
    if (cstr) {
        res = GPath::autoAlloc();
        res->set(cstr);
        jniEnv->ReleaseStringUTFChars(str, cstr);
    }
    jniEnv->DeleteLocalRef(str);
    return res;
}

void GJavaCAPI::appTerminate(JNIEnv *jniEnv) {
    callStaticVoidMethod(jniEnv, (int) APIM_AppTerminate, GX::JavaGetMainInstance());
}

void GJavaCAPI::UUIDCreate(JNIEnv *jniEnv, guint8 *uuidOut) {
    jbyteArray barr = (jbyteArray) callStaticObjectMethod(jniEnv, APIM_UUIDCreate);

    jbyte *ba = jniEnv->GetByteArrayElements(barr, JNI_FALSE);

    memcpy(uuidOut, ba, 16);

    jniEnv->ReleaseByteArrayElements(barr, ba, 0);

    jniEnv->DeleteLocalRef(barr);
}

#endif
