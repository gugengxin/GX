//
// Created by Gengxin Gu on 2016/12/9.
//

#include "GAndroid.h"
#if defined(GX_OS_ANDROID)


GAndroid* GAndroid::shared()
{
    static GAndroid g_Obj;
    return &g_Obj;
}

GAndroid::GAndroid()
{

}

GAndroid::~GAndroid()
{

}




#endif