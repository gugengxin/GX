//
// Created by Gengxin Gu on 2017/4/21.
//

#include "GAndroidActivity.h"
#if defined(GX_OS_ANDROID)

GAndroidActivity::GAndroidActivity()
{

}

GAndroidActivity::~GAndroidActivity()
{

}





////////////////////////////////////////////////////////////

JNIEXPORT jlong JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnCreate
        (JNIEnv *, jobject)
{
    GAndroidActivity* entrance=new GAndroidActivity();
    return GAndroidEntrance::add(entrance);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnRestart
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnStart
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnResume
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnPause
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnStop
        (JNIEnv *, jobject, jlong)
{

}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnDestroy
        (JNIEnv *env, jobject sender, jlong bridgeID)
{
    GAndroidActivity* entrance=GX_CAST_R(GAndroidActivity*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnDestory(env,sender);
    GAndroidEntrance::remove(entrance);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnWindowCreated
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface, jstring gameClassName)
{
    GAndroidActivity* entrance=GX_CAST_R(GAndroidActivity*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowCreated(env,sender,win,surface,gameClassName);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnWindowChanged
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface, jint width, jint height)
{
    GAndroidActivity* entrance=GX_CAST_R(GAndroidActivity*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowChanged(env,sender,win,surface,width,height);
}

JNIEXPORT void JNICALL Java_com_gxengine_game_GAndroidActivity_jniOnWindowDestroyed
        (JNIEnv *env, jobject sender, jlong bridgeID, jobject win, jobject surface)
{
    GAndroidActivity* entrance=GX_CAST_R(GAndroidActivity*,GAndroidEntrance::get(bridgeID));
    entrance->jniOnWindowDestroyed(env,sender,win,surface);
}



#endif