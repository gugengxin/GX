//
// Created by Gengxin Gu on 2017/4/21.
//

#ifndef AS_GANDROIDACTIVITY_H
#define AS_GANDROIDACTIVITY_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)
#include "GAndroidEntrance.h"
#include "com_gxengine_game_GAndroidActivity.h"

class GAndroidActivity : public GAndroidEntrance {
    friend jlong Java_com_gxengine_game_GAndroidActivity_jniOnCreate(JNIEnv *, jobject);
private:
    GAndroidActivity();
    virtual ~GAndroidActivity();

private:

};


#endif

#endif //AS_GANDROIDACTIVITY_H
