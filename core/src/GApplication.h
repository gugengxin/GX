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
#include "GString.h"
#if defined(GX_OS_ANDROID)
#include <android/input.h>
#include <android/native_activity.h>
#include "com_gxengine_core_GAndroidApp.h"
#elif defined(GX_OS_QT)
#include <QTimer>
#elif defined(GX_OS_WINDOWS)
#include "GXCWnd.h"
#endif

#include "GXGObject.h"

class GApplication
#if defined(GX_OS_QT)
        : public QObject
#endif
{
#if defined(GX_OS_QT)
        Q_OBJECT
#endif
public:
    static const GString* const memoryWarningNotification;
public:
    class Delegate : public GObject {
        GX_GOBJECT(Delegate);
    public:
        virtual void appDidFinishLaunching(GApplication* application,int argc, char *argv[]) {
            GX_UNUSED(application)
            GX_UNUSED(argc)
            GX_UNUSED(argv)
        }
		virtual void appWillTerminate(GApplication* application){
			GX_UNUSED(application)
		}
        virtual void appReceivedMemoryWarning(GApplication* application){
			GX_UNUSED(application)
		}
    public://for game
        virtual gint windowsSuggestedSamples() {
            return 0;
        }
        virtual gint windowsSuggestedDepth() {
            return 24;
        }
        virtual gint windowsSuggestedStencil() {
            return 8;
        }
    };
    
    class Component {
    public:
        Component() {}
        virtual ~Component() {}
        
        virtual gint getAppCID()=0;//唯一标识
        virtual void idle()=0;
    };
	
public:
    static GApplication* shared();
	static GApplication::Delegate* sharedDelegate();
    static void main(int argc, char *argv[], const char* delegateClassName);
private:
    GApplication();
    ~GApplication();
    
public:
    void addComponent(Component* v);
    void removeComponent(Component* v);
    Component* firstComponent(gint cid);
    

#if defined(GX_OS_QT)
private slots:
    void idle();
private:
#else
    void idle();
#endif
private:
	void eventDidFinishLaunching(int argc, char *argv[]);
	void eventWillTerminate();
	void eventReceivedMemoryWarning();

private:
    Delegate* m_Delegate;
    GPDArray<Component*> m_Components;
    
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

#include "GXGObjectUD.h"

#endif /* GApplication_h */
