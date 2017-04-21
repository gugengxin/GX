//
// Created by Gengxin Gu on 2017/4/21.
//

#include "GAndroidEntrance.h"
#if defined(GX_OS_ANDROID)

gint64 GAndroidEntrance::add(GAndroidEntrance* v)
{
    return GX_CAST_S(gint64,GX_CAST_R(gint,v));
}
void GAndroidEntrance::remove(GAndroidEntrance* v)
{
    delete v;
}
GAndroidEntrance* GAndroidEntrance::get(gint64 bridgeID)
{
    return GX_CAST_R(GAndroidEntrance*,GX_CAST_S(gint,bridgeID));
}



GAndroidEntrance::GAndroidEntrance()
{
    m_Window=NULL;
}

GAndroidEntrance::~GAndroidEntrance()
{
}

void GAndroidEntrance::jniOnDestory(JNIEnv *env, jobject sender)
{
    m_Window->eventDestroy();
}

void GAndroidEntrance::jniOnWindowCreated(JNIEnv *env, jobject sender, jobject win, jobject surface, jstring gameClassName)
{
    ANativeWindow* nw=ANativeWindow_fromSurface(env,surface);
    if (!m_Window) {
        const char *cstr = env->GetStringUTFChars(gameClassName, NULL);

        m_Window=GWindow::main(nw,cstr);

        env->ReleaseStringUTFChars(gameClassName, cstr);
    }
    else {
        m_Window->androidRecreate(nw);
    }
    ANativeWindow_release(nw);
}
void GAndroidEntrance::jniOnWindowChanged(JNIEnv *env, jobject sender, jobject win, jobject surface, jint width, jint height)
{
    m_Window->eventResize();
}
void GAndroidEntrance::jniOnWindowDestroyed(JNIEnv *env, jobject sender, jobject win, jobject surface)
{
    m_Window->androidDestroy();
}


#endif