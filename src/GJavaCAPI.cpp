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


GJavaCAPI* GJavaCAPI::Shared()
{
	static GJavaCAPI gav_Cls;

	if (gav_Cls.GetClass()==NULL) {
		GJavaJNIEnvAutoPtr jniEnv;

		gav_Cls.SetClass(jniEnv.Get(), "com/gxengine/gx/GJavaCAPI");

		gav_Cls.SetMethod(jniEnv.Get(),
				APIM_AppGetDefaultWindowScaleActivity,
				"AppGetDefaultWindowScale",
				"(Landroid/app/Activity;)F",
				true);
		gav_Cls.SetMethod(jniEnv.Get(),
				APIM_AppGetDefaultWindowScaleDreamService,
				"AppGetDefaultWindowScale",
				"(Landroid/service/dreams/DreamService;)F",
				true);
		gav_Cls.SetMethod(jniEnv.Get(), APIM_AppGetCacheDir,
				"AppGetCacheDir", "(Landroid/content/ContextWrapper;)Ljava/lang/String;", true);
		gav_Cls.SetMethod(jniEnv.Get(), APIM_AppGetPackageCodePath,
				"AppGetPackageCodePath", "(Landroid/content/ContextWrapper;)Ljava/lang/String;", true);
		gav_Cls.SetMethod(jniEnv.Get(), APIM_AppTerminate,
						"AppTerminate", "(Landroid/app/Activity;)V", true);

		gav_Cls.SetMethod(jniEnv.Get(), APIM_UUIDCreate,"UUIDCreate","()[B",true);
	}

	return &gav_Cls;
}

float GJavaCAPI::AppGetDefaultWindowScale(JNIEnv* jniEnv)
{
	if(GX::JavaMainInstanceIsActivity()) {
		return CallStaticFloatMethod(jniEnv,(int)APIM_AppGetDefaultWindowScaleActivity, GX::JavaGetMainInstance());
	}
	return CallStaticFloatMethod(jniEnv,(int)APIM_AppGetDefaultWindowScaleDreamService, GX::JavaGetMainInstance());
}

void GJavaCAPI::AppTerminate(JNIEnv* jniEnv)
{
	CallStaticVoidMethod(jniEnv,(int)APIM_AppTerminate, GX::JavaGetMainInstance());
}

void GJavaCAPI::UUIDCreate(JNIEnv* jniEnv,guint8 * uuidOut)
{
	jbyteArray barr= (jbyteArray)CallStaticObjectMethod(jniEnv,APIM_UUIDCreate);

	jbyte* ba = jniEnv->GetByteArrayElements(barr, JNI_FALSE);

	memcpy(uuidOut,ba,16);

	jniEnv->ReleaseByteArrayElements(barr, ba, 0);

	jniEnv->DeleteLocalRef(barr);
}

#endif
