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
class GWindow;

class GApplication {
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
		virtual void appCreate(GApplication* application) {}
		virtual void appStart(GApplication* application) {}
		virtual void appResume(GApplication* application) {}
		virtual void appPause(GApplication* application) {}
		virtual void appStop(GApplication* application) {}
		virtual void appDestroy(GApplication* application) {}

		virtual GWindow* appCanCreateWindow(GApplication* application,void* osWindow) {
			return NULL;
		}
		virtual void appReceivedMemoryWarning(GApplication* application){}

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
    
    void idle();

	void eventCreate();
	void eventStart();
	void eventResume();
	void eventPause();
	void eventStop();
	void eventDestroy();

	void setCanCreateWindow(void* osWindow);

public:
    GWindow* firstWindow() {
        return m_Windows.first();
    }
	gint getWindowCount() {
		return m_Windows.getCount();
	}

	GWindow* getWindow(gint idx) {
		return m_Windows.get(idx);
	}

	void addWindow(GWindow* win);


private:
    Delegate* m_Delegate;
    GArray<GWindow> m_Windows;
	InitData m_InitData;
    
#if defined(GX_OS_APPLE)
    friend class _AppBridge;
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
	friend void Java_com_gxengine_gx_GJavaJAPI_mainWindowHasCreated
			(JNIEnv *, jclass, jobject);
#endif
};



#endif /* GApplication_h */
