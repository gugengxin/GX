//
// Created by Gengxin Gu on 2017/4/21.
//

#ifndef AS_GANDROIDDAYDREAM_H
#define AS_GANDROIDDAYDREAM_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)
#include "GAndroidEntrance.h"
#include "com_gxengine_game_GAndroidDaydream.h"

class GAndroidDaydream : public GAndroidEntrance {
    friend jlong Java_com_gxengine_game_GAndroidDaydream_jniOnCreate(JNIEnv *, jobject);
private:
    GAndroidDaydream();
    virtual ~GAndroidDaydream();

private:

};



#endif

#endif //AS_GANDROIDDAYDREAM_H
