//
// Created by Gengxin Gu on 2017/4/21.
//

#ifndef AS_GANDROIDENTRANCE_H
#define AS_GANDROIDENTRANCE_H

#include "GXPrefix.h"

#if defined(GX_OS_ANDROID)

#include "GWindow.h"

class GAndroidEntrance {
public:
    static gint64 add(GAndroidEntrance* v);
    static void remove(GAndroidEntrance* v);
    static GAndroidEntrance* get(gint64 bridgeID);
protected:
    GAndroidEntrance();
    virtual ~GAndroidEntrance();

public:
    void jniOnDestory(JNIEnv *env, jobject sender);
    void jniOnWindowCreated(JNIEnv *env, jobject sender, jobject win, jobject surface, jstring gameClassName);
    void jniOnWindowChanged(JNIEnv *env, jobject sender, jobject win, jobject surface, jint width, jint height);
    void jniOnWindowDestroyed(JNIEnv *env, jobject sender, jobject win, jobject surface);
public:

private:
    GWindow* m_Window;
};

#endif

#endif //AS_GANDROIDENTRANCE_H
