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
#include "GXContext.h"
#include "GContext.h"
#include "GXCWnd.h"
#include "GColor.h"
#include "GCanvas.h"
#include "GGame.h"
#if defined(GX_OS_ANDROID)
#include <android/native_window.h>
#include <android/native_window_jni.h>
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


#include "GXGObject.h"

class GWindow {
	friend class GApplication;
    friend class GX_CONTEXT_BASE;
private:
    class Canvas : public GCanvas {
        friend class GWindow;
        GX_GOBJECT(Canvas);
    public:
        virtual float getWidth();
        virtual float getHeight();
        virtual float getScale();
        
    private:
        inline void setWindow(GWindow* v) {
            m_Window=v;
        }
    private:
        GWindow* m_Window;
    };
private:
	GWindow(void* osWinP, GClass* gameGClass);
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
    const GColor4F getBackgroundColor() const {
        return m_Canvas->getBackgroundColor();
    }
    
    inline GContext& getContext() {
        return m_Context;
    }
    inline GCanvas* getCanvas() {
        return m_Canvas;
    }
    
public:
	void idle();
	void render();
private:
	void eventAttachToApp();
	void eventDetachFromApp();
    void eventResize();
    void eventDestroy();//依附的系统窗口销毁时调用

private:
	GContext m_Context;
    Canvas*  m_Canvas;
private:
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
	void androidDestroy();
	void androidRecreate(ANativeWindow* nw);

    float m_OSWinScale;
	ANativeWindow* m_OSWin;
#elif defined(GX_OS_QT)
    friend class _GQWindow;
    _GQWindow* m_OSWin;
    QWidget* m_Container;
#endif
private:
	GGame* m_Game;
};

#include "GXGObjectUD.h"

#endif /* GWindow_h */
