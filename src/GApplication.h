//
//  GApplication.h
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GApplication_h
#define GApplication_h

#include "GXPrefix.h"
#include "GArray.h"
#include "GWindow.h"
#include "GXCWnd.h"
#if defined(GX_OS_ANDROID)
#include <android/input.h>
#include <android/native_activity.h>
#include "com_gxengine_gx_GJavaJAPI.h"
#endif

class GApplication {
public:
    class Delegate {
    public:

    };
public:
    static GApplication* shared();
    static void main(Delegate* dge);
private:
    GApplication();
    ~GApplication();
    
    void idle();
    
    void didFinishLaunching();
    void didBecomeActive();
    void willResignActive();
    void didEnterBackground();
    void willEnterForeground();
    void willTerminate();
    void didReceiveMemoryWarning();
public:

private:
    Delegate* m_Delegate;
    GArray<GWindow> m_Windows;
    
#if defined(GX_OS_APPLE)
    friend class _AppTimerBridge;
    void* m_Timer;
#elif defined(GX_OS_WINDOWS)
	static LRESULT CALLBACK winMsgWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void CALLBACK winTimerCallBack(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void createWinMsgWndAndStart();
	void destroyWinMsgWnd();

	GX::CWnd m_MsgWnd;
	UINT m_TimerID;
#elif defined(GX_OS_ANDROID)
    friend void Java_com_gxengine_gx_GJavaJAPI_appCreate
            (JNIEnv *, jclass, jint, jobject);
    friend void Java_com_gxengine_gx_GJavaJAPI_appStart
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appResume
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appIdle
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appPause
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appStop
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appDestroy
            (JNIEnv *, jclass);
    friend void Java_com_gxengine_gx_GJavaJAPI_appLowMemory
            (JNIEnv *, jclass);
    void androidAppCreate();
    void androidAppStart();
    void androidAppResume();
    void androidAppPause();
    void androidAppStop();
    void androidAppDestroy();
    void androidAppLowMemory();

//    void androidWindowCreated(ANativeWindow*);
//    void androidWindowChanged();
//    void androidWindowDestroyed();
//    void androidWindowOnTouchEvent(jint action,jint pointerId,jfloat x,jfloat y);


#endif
};



#endif /* GApplication_h */
