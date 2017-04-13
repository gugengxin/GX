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
#include "GDataArray.h"
#if defined(GX_OS_ANDROID)
#include <android/input.h>
#include <android/native_activity.h>
#elif defined(GX_OS_QT)
#include <QTimer>
#endif

class GApplication
#if defined(GX_OS_QT)
        : public QObject
#endif
{
#if defined(GX_OS_QT)
        Q_OBJECT
#endif
    friend class GWindow;
public:
	class Delegate {
    public:
        virtual void appDidFinishLaunching(GApplication* application) {
            GX_UNUSED(application)
        }
		virtual void appWillTerminate(GApplication* application){
			GX_UNUSED(application)
		}
        virtual void appReceivedMemoryWarning(GApplication* application){
			GX_UNUSED(application)
		}
    };
	
public:
    static GApplication* shared();
	static GApplication::Delegate* sharedDelegate();
	static void main(Delegate* dge);
private:
    GApplication();
    ~GApplication();

#if defined(GX_OS_QT)
private slots:
    void idle();
private:
#else
    void idle();
#endif
private:
	void eventDidFinishLaunching();
	void eventWillTerminate();
	void eventReceivedMemoryWarning();

private:
    Delegate* m_Delegate;
    
#if defined(GX_OS_APPLE)
    friend class _AppBridge;
    void* m_Helper;
#elif defined(GX_OS_WINDOWS)
	static LRESULT CALLBACK winMsgWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void CALLBACK winTimerCallBack(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void createWinMsgWndAndStart();
	void destroyWinMsgWnd();

	GX::CWnd m_MsgWnd;
	UINT m_TimerID;
#elif defined(GX_OS_ANDROID)
    friend void Java_com_gxengine_core_GAndroidApp_jniOnTerminate(JNIEnv *, jobject);
    friend void Java_com_gxengine_core_GAndroidApp_jniOnLowMemory(JNIEnv *, jobject);
    friend void Java_com_gxengine_core_GAndroidApp_jniIdle(JNIEnv *, jobject);
#elif defined(GX_OS_QT)
    QTimer m_Timer;
#endif
};



#endif /* GApplication_h */
