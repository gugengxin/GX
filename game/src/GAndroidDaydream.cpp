//
// Created by Gengxin Gu on 2017/4/21.
//

#include "GAndroidDaydream.h"
#if defined(GX_OS_ANDROID)

GAndroidDaydream::GAndroidDaydream()
{

}

GAndroidDaydream::~GAndroidDaydream()
{

}


////////////////////////////////////////////////

JNIEXPORT jlong JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnCreate
        (JNIEnv *, jobject)
{
    GAndroidDaydream* entrance=new GAndroidDaydream();
    return GAndroidEntrance::add(entrance);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnAttachedToWindow
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnDreamingStarted
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnDreamingStopped
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnDetachedFromWindow
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnDestroy
        (JNIEnv *env, jobject sender, jlong bridgeID)
{
    GAndroidDaydream* entrance=GX_CAST_R(GAndroidDaydream*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnDestory(env,sender);
    GAndroidEntrance::remove(entrance);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnWindowCreated
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface, jstring gameClassName)
{
    GAndroidDaydream* entrance=GX_CAST_R(GAndroidDaydream*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowCreated(env,sender,win,surface,gameClassName);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnWindowChanged
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface, jint width, jint height)
{
    GAndroidDaydream* entrance=GX_CAST_R(GAndroidDaydream*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowChanged(env,sender,win,surface,width,height);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidDaydream_jniOnWindowDestroyed
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface)
{
    GAndroidDaydream* entrance=GX_CAST_R(GAndroidDaydream*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowDestroyed(env,sender,win,surface);
}

#endif