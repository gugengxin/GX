//
//  GWindow.cpp
//  GX
//
//  Created by Gengxin Gu on 16/5/3.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GWindow.h"
#include "GSystem.h"
#include "GLog.h"

#if defined(GX_OS_WINDOWS)

#define M_OS_WND(p) GX_CAST_R(HWND,p)

static void SetWindowToHWND(HWND hWnd, GWindow* win)
{
#if GX_PTR_64BIT
	::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)win);
#else
	::SetWindowLong(hWnd, GWL_USERDATA, (LONG)win);
#endif
}
static GWindow* GetWindowFromHWND(HWND hWnd)
{
#if GX_PTR_64BIT
	return (GWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
	return (GWindow*)::GetWindowLong(hWnd, GWL_USERDATA);
#endif
}

LRESULT CALLBACK GWindow::wndProcP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GWindow* win = GetWindowFromHWND(hWnd);

	switch (message)
	{
	case WM_SIZE:
	case WM_SIZING:
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::MoveWindow(win->m_OSWin.getHWND(), 0, 0, rc.right - rc.left, rc.bottom - rc.top, FALSE);
		win->renderForce();
	}
	break;
	default:
		break;
	}


	return CallWindowProc(win->m_WndProcP, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK GWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GWindow* win = GetWindowFromHWND(hWnd);

	switch (message)
	{
	case WM_DESTROY: {
		win->m_OSWin.releaseHWND();
	}
	break;
	case WM_SIZE: {
		//GX_LOG_W(PrioDEBUG, "GWindow", "wndProc WM_SIZE");
	}
	break;
	case WM_PAINT: {
		win->renderForce();
	}
	default:
		break;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

#endif













GX_OBJECT_IMPLEMENT(GWindow, GObject);


GWindow::GWindow()
{
	m_RenderStepTime=1000/30;
	m_RenderLastTime=0;
	m_OSWinP = NULL;
#if defined(GX_OS_WINDOWS)
	m_WndProcP=NULL;
#else
	m_OSWin = NULL;
#endif
}	

GWindow::~GWindow()
{
	m_Context.destroy();
}

bool GWindow::create(void* osWinP)
{
#if defined(GX_OS_WINDOWS)
	if (m_OSWin.getHWND() || !osWinP) {
		return false;
	}
#else
	if (m_OSWin || !osWinP) {
		return false;
	}
#endif
	m_OSWinP = osWinP;

#if defined(GX_OS_WINDOWS)
	WNDCLASS	wc;						// 窗口类结构
	DWORD		dwExStyle;				// 扩展窗口风格
	DWORD		dwStyle;				// 窗口风格
	RECT		rc;

	memset(&wc, 0, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// 移动时重画，并为窗口取得DC
	wc.lpfnWndProc = (WNDPROC)wndProc;					// WndProc处理消息
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// 装入鼠标指针

	::GetClientRect(M_OS_WND(m_OSWinP), &rc);

	dwExStyle = WS_EX_APPWINDOW;			// 扩展窗体风格
	dwStyle = WS_CHILDWINDOW;

	m_OSWin.create(wc, dwStyle, dwExStyle, rc, M_OS_WND(m_OSWinP));
	SetWindowToHWND(m_OSWin.getHWND(),this);
#if GX_PTR_64BIT
	m_WndProcP = (WNDPROC)SetWindowLong(M_OS_WND(m_OSWinP), GWLP_WNDPROC, (LONG)wndProcP);
#else
	m_WndProcP = (WNDPROC)SetWindowLong(M_OS_WND(m_OSWinP), GWL_WNDPROC, (LONG)wndProcP);
#endif
	GX_ASSERT(!GetWindowFromHWND(M_OS_WND(m_OSWinP)));
	SetWindowToHWND(M_OS_WND(m_OSWinP), this);

	::ShowWindow(m_OSWin.getHWND(), SW_SHOW);
	UpdateWindow(m_OSWin.getHWND());
#endif

	m_Context.create(this);

	return true;
}



void GWindow::idle()
{

}
void GWindow::render()
{

}

void GWindow::renderForce()
{
	m_RenderLastTime = GSystem::currentTimeMS();

	m_Context.renderBegin();

	this->render();

	m_Context.renderEnd();
}

void GWindow::renderIfNeed()
{
	if (GSystem::currentTimeMS() - m_RenderLastTime >= m_RenderStepTime) {
		renderForce();
	}
}
