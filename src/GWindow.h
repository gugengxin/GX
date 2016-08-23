//
//  GWindow.h
//  GX
//
//  Created by Gengxin Gu on 16/5/3.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GWindow_h
#define GWindow_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GContext.h"
#include "GXCWnd.h"
#include "GColor.h"
#if defined(GX_OS_ANDROID)
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "com_gxengine_gx_GJavaJAPI.h"
#elif defined(GX_OS_QT)
#include <QWindow>

class GWindow;

class _GQWindow : public QWindow
{
    Q_OBJECT
public:
    _GQWindow();
    virtual ~_GQWindow();

    void setDelegate(GWindow* v) {
        m_Delegate=v;
    }
protected:
private:
    GWindow* m_Delegate;
};

#endif

class GWindow {
	friend class GApplication;
#if defined(GX_OPENGL)
	friend class GOGLContext;
#elif defined(GX_METAL)
    friend class GMTLContext;
#endif
private:
	GWindow(void* osWinP);
	~GWindow();
public:
	inline void* getOSWindow() {
#if defined(GX_OS_WINDOWS)
		return m_OSWin.getHWND();
#else
		return m_OSWin;
#endif
	}
    float getWidth();
    float getHeight();
    float getScale();
    
public:
	void idle();
	void renderIfNeed();
protected:
	void renderForce();
	void render();
protected:
    void eventResize();
    void eventDestroy();

private:
	GContext m_Context;
	gint	m_RenderStepTime;
	gint64	m_RenderLastTime;
    GColor4F m_BgdColor;

	void* m_OSWinP;
#if defined(GX_OS_WINDOWS)
	static LRESULT CALLBACK wndProcP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	GX::CWnd m_OSWin;
	WNDPROC m_WndProcP;
#elif defined(GX_OS_APPLE)
    friend class _WindowBridge;
#if defined(GX_METAL)
    void* getMetalLayer();
#endif

	void* m_OSWin;
	void* m_OSWinCtrler;
#elif defined(GX_OS_ANDROID)
	friend void Java_com_gxengine_gx_GJavaJAPI_mainWindowHasCreated(JNIEnv *env, jclass, jobject surface);
	friend void Java_com_gxengine_gx_GJavaJAPI_mainWindowHasChanged(JNIEnv *, jclass, jobject, jint, jint);
	friend void Java_com_gxengine_gx_GJavaJAPI_mainWindowHasDestroyed(JNIEnv *, jclass, jobject);
	void androidDestroy();
	void androidRecreate(ANativeWindow* nw);

    float m_OSWinScale;
	ANativeWindow* m_OSWin;
#elif defined(GX_OS_QT)
    friend class _GQWindow;
    _GQWindow* m_OSWin;
    QWidget* m_Container;
#endif
};



#endif /* GWindow_h */
