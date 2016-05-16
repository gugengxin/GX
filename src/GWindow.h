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
#if defined(GX_OS_ANDROID)
#include <android/native_window.h>
#include <android/native_window_jni.h>
#endif

class GWindow : public GObject {
#if defined(GX_OPENGL)
	friend class GOGLContext;
#endif
    GX_OBJECT(GWindow);
public:
	inline void* getOSWindow() {
#if defined(GX_OS_WINDOWS)
		return m_OSWin.getHWND();
#else
		return m_OSWin;
#endif
	}
	bool create(void* osWinP);
    
public:
	virtual void idle();
	void renderIfNeed();
protected:
	void renderForce();
	virtual void render();

private:
	GContext m_Context;
	gint	m_RenderStepTime;
	gint64	m_RenderLastTime;

	void* m_OSWinP;
#if defined(GX_OS_WINDOWS)
	GX::CChildWnd m_OSWin;
	WNDPROC m_WndProcP;
#elif defined(GX_OS_APPLE)
	void* m_OSWin;
	void* m_OSWinCtrler;
#elif defined(GX_OS_ANDROID)
	ANativeWindow* m_OSWin;
#endif
private:
#if defined(GX_OS_WINDOWS)
	static LRESULT CALLBACK wndProcP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif
};



#endif /* GWindow_h */
