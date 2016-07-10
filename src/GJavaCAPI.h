//
// Created by Gengxin Gu on 16/5/5.
//

#ifndef AS_GJAVACAPI_H
#define AS_GJAVACAPI_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)
#include "GJavaAPI.h"
#include "GJavaClass.h"
#include "GTString.h"


class GJavaCAPI : public GJavaClass<6> {
public:
	static GJavaCAPI* shared();

	float appGetDefaultWindowScale(JNIEnv* jniEnv);
	GPath* appGetCacheDir(JNIEnv* jniEnv);
	GPath* appGetPackageCodePath(JNIEnv* jniEnv);
	void appTerminate(JNIEnv* jniEnv);
	void UUIDCreate(JNIEnv* jniEnv,guint8* uuidOut);
};


#endif


#endif //AS_GJAVACAPI_H
