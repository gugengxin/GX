//
// Created by Gengxin Gu on 16/4/20.
//

#include "AppDge.h"


#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT void JNICALL Java_com_gxengine_GX_main
(JNIEnv *, jclass, jint)
{
    GApplication::InitData initData;

    GApplication::main(AppDge::shared(),&initData);
}

#ifdef __cplusplus
}
#endif

