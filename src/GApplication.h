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
#include "GWindow.h"
#include "GXCWnd.h"
#if defined(GX_OS_ANDROID)
#include <android/input.h>
#include <android/native_activity.h>
#include "com_gxengine_gx_GJavaJAPI.h"
#elif defined(GX_OS_QT)
#include <QTimer>
#endif
class GWindow;

class GApplication
#if defined(GX_OS_QT)
        : public QObject
#endif
{
#if defined(GX_OS_QT)
        Q_OBJECT
#endif
public:
	class InitData {
	public:
        InitData() {
            m_OSWindow=NULL;
        }
		InitData(void* osWin) {
			m_OSWindow = osWin;
		}
		~InitData() {

		}

		void* getOSWindow() {
			return m_OSWindow;
		}

	private:
		void* m_OSWindow;
	};

    class Delegate {
    public:
        virtual void appCreate(GApplication* application) {GX_UNUSED(application)}
        virtual void appStart(GApplication* application) {GX_UNUSED(application)}
        virtual void appResume(GApplication* application) {GX_UNUSED(application)}
        virtual void appPause(GApplication* application) {GX_UNUSED(application)}
        virtual void appStop(GApplication* application) {GX_UNUSED(application)}
        virtual void appDestroy(GApplication* application) {GX_UNUSED(application)}

		virtual void appCanCreateWindow(GApplication* application,void* osWindow) {
            GX_UNUSED(application)
            GX_UNUSED(osWindow)
		}
        virtual void appReceivedMemoryWarning(GApplication* application){GX_UNUSED(application)}

		virtual gint windowsSuggestedSamples() {
			return 4;
		}
		virtual gint windowsSuggestedDepth() {
			return 24;
		}
		virtual gint windowsSuggestedStencil() {
			return 8;
		}
    };
	
public:
    static GApplication* shared();
	static GApplication::Delegate* sharedDelegate();
	static void main(Delegate* dge, InitData* initData);
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

	void eventCreate();
	void eventStart();
	void eventResume();
	void eventPause();
	void eventStop();
	void eventDestroy();

	void setCanCreateWindow(void* osWindow);

public:
    void addWindow(void* osWin);
    GWindow* firstWindow();
    gint getWindowCount();
    GWindow* getWindow(gint idx);
    void removeWindow(GWindow* win);

private:
    Delegate* m_Delegate;
    GPDArray<GWindow*> m_Windows;
	InitData m_InitData;
    
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
	friend void Java_com_gxengine_gx_GJavaJAPI_mainWindowHasCreated
			(JNIEnv *, jclass, jobject);
#elif defined(GX_OS_QT)
    QTimer m_Timer;
#endif
};



#endif /* GApplication_h */
