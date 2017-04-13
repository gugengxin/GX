//
// Created by Gengxin Gu on 16/4/20.
//

#include "AppDge.h"

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT void JNICALL Java_com_gxengine_core_GAndroidApp_jniMain(JNIEnv *, jobject)
{
    GApplication::main(AppDge::shared());
}

#ifdef __cplusplus
}
#endif

