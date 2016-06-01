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
#include "GApplication.h"

#if defined(GX_OS_WINDOWS)

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
	if (win) {
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
	}
	return CallWindowProc(win->m_WndProcP, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK GWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GWindow* win = GetWindowFromHWND(hWnd);
	if (win) {
		switch (message)
		{
		case WM_DESTROY: {
			win->m_OSWin.releaseHWND();
		}
						 break;
		case WM_SIZE:
		case WM_SIZING: {
			//GX_LOG_W(PrioDEBUG, "GWindow", "wndProc WM_SIZE");
			win->eventResize();
		}
						break;
		case WM_PAINT: {
			
		}
		default:
			break;
		}
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

#elif defined(GX_OS_APPLE)
#if defined(GX_OS_IPHONE)
#import <UIKit/UIKit.h>
#elif defined(GX_OS_MACOSX)
#import <Cocoa/Cocoa.h>
#endif

class _WindowBridge {
public:
    inline GWindow* getTarget() {
        return m_Target;
    }
    inline void setTarget(GWindow* v) {
        m_Target=v;
    }
    
    inline void eventResize() {
        m_Target->eventResize();
    }
    
    
private:
    GWindow* m_Target;
};

@interface _OGLView :
#if defined(GX_OS_IPHONE)
UIView
#elif defined(GX_OS_MACOSX)
NSView
#endif
{
    _WindowBridge _bridge;
}

@end

@implementation _OGLView

- (id)initWithDelegate:(GWindow*)dge frame:(CGRect)rc
{
    self = [super initWithFrame:rc];
    if (self) {
        _bridge.setTarget(dge);
#if defined(GX_OS_IPHONE)
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        self.contentScaleFactor=[UIScreen mainScreen].scale;
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = @{
        kEAGLDrawablePropertyRetainedBacking: [NSNumber numberWithBool:NO],
        kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8
        };
#if defined(GX_OS_IOS)
        self.multipleTouchEnabled=YES;
#endif
        
#elif defined(GX_OS_MACOSX)
        self.autoresizingMask=NSViewWidthSizable|NSViewHeightSizable;
        
        [self setWantsBestResolutionOpenGLSurface:YES];
        
        NSNotificationCenter* nc=[NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(noteWindowWillClose:) name:NSWindowWillCloseNotification object:nil];
#endif
    }
    return self;
}

- (void)dealloc
{
#if defined(GX_OS_MACOSX)
    [[NSNotificationCenter defaultCenter] removeObserver:self];
#endif
    [super dealloc];
}

#if defined(GX_OS_IPHONE)
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    _bridge.eventResize();
    
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}

#elif defined(GX_OS_MACOSX)

- (void)resizeWithOldSuperviewSize:(NSSize)oldSize
{
    [super resizeWithOldSuperviewSize:oldSize];
    
    _bridge.eventResize();
}

- (void)mouseDown:(NSEvent *)theEvent
{
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
}

- (void)otherMouseDown:(NSEvent *)theEvent
{
}

- (void)mouseDragged:(NSEvent *)theEvent
{
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
}

- (void)mouseUp:(NSEvent *)theEvent
{
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
}

- (void)mouseMoved:(NSEvent *)theEvent
{
}

- (void)scrollWheel:(NSEvent *)theEvent
{
}

- (void)keyDown:(NSEvent *)theEvent
{
}
- (void)keyUp:(NSEvent *)theEvent
{
}

- (void)noteWindowWillClose:(NSNotification*)note
{
    NSWindow* win;
    if ([_window isKindOfClass:[NSWindow class]]) {
        win=_window;
    }
    else {
        win=[(NSView*)_window window];
    }
    if (note.object==win) {
        
    }
}

#endif

@end


@interface _OGLViewController :
#if defined(GX_OS_IPHONE)
UIViewController
#elif defined(GX_OS_MACOSX)
NSViewController
#endif
{
    _WindowBridge _bridge;
}


@end

@implementation _OGLViewController

- (id)initWithDelegate:(GWindow*)dge view:(_OGLView*)vw
{
    self=[super initWithNibName:nil bundle:nil];
    if (self) {
        _bridge.setTarget(dge);
        self.view=vw;
    }
    return self;
}

- (void)dealloc
{
 
    [super dealloc];
}

- (void)loadView
{
}

@end

#elif defined(GX_OS_ANDROID)

#include "GJavaCAPI.h"

void GWindow::androidDestory()
{
	m_Context.destroy();
	if(m_OSWin) {
		ANativeWindow_release(GX_CAST_R(ANativeWindow*,m_OSWin));
		m_OSWin=NULL;
	}
}
void GWindow::androidRecreate(ANativeWindow* nw)
{
	create(nw);
}

#elif defined(GX_OS_QT)

#endif





GX_OBJECT_IMPLEMENT(GWindow, GObject);


GWindow::GWindow()
{
	m_RenderStepTime=1000/30;
	m_RenderLastTime=0;
	m_OSWinP = NULL;
#if defined(GX_OS_WINDOWS)
	m_WndProcP=NULL;
#elif defined(GX_OS_APPLE)
	m_OSWin=NULL;
	m_OSWinCtrler=NULL;
#elif defined(GX_OS_ANDROID)
	m_OSWin = NULL;
	m_OSWinScale=0.0f;
#elif defined(GX_OS_QT)
    m_OSWin=NULL;
    m_Container=NULL;
#endif
}	

GWindow::~GWindow()
{
	m_Context.destroy();
#if defined(GX_OS_APPLE)
    [GX_CAST_R(id, m_OSWin) release];
    [GX_CAST_R(id, m_OSWinCtrler) release];
#elif defined(GX_OS_ANDROID)
    if(m_OSWin) {
    	ANativeWindow_release(GX_CAST_R(ANativeWindow*,m_OSWin));
    }
#elif defined(GX_OS_QT)
    //delete m_OSWin;
    //delete m_Container;
#endif
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

	::GetClientRect(GX_CAST_R(HWND, m_OSWinP), &rc);

	dwExStyle = WS_EX_APPWINDOW;			// 扩展窗体风格
	dwStyle = WS_CHILDWINDOW;

	m_OSWin.create(wc, dwStyle, dwExStyle, rc, GX_CAST_R(HWND, m_OSWinP));
	SetWindowToHWND(m_OSWin.getHWND(),this);
#if GX_PTR_64BIT
	m_WndProcP = (WNDPROC)SetWindowLongPtr(GX_CAST_R(HWND, m_OSWinP), GWLP_WNDPROC, (LONG_PTR)wndProcP);
#else
	m_WndProcP = (WNDPROC)SetWindowLong(GX_CAST_R(HWND, m_OSWinP), GWL_WNDPROC, (LONG)wndProcP);
#endif
	GX_ASSERT(!GetWindowFromHWND(GX_CAST_R(HWND, m_OSWinP)));
	SetWindowToHWND(GX_CAST_R(HWND, m_OSWinP), this);

	::ShowWindow(m_OSWin.getHWND(), SW_SHOW);
	UpdateWindow(m_OSWin.getHWND());
    
#elif defined(GX_OS_IPHONE)
    m_OSWin=[[_OGLView alloc] initWithDelegate:this frame:GX_CAST_R(UIView*, osWinP).bounds];
    m_OSWinCtrler=[[_OGLViewController alloc] initWithDelegate:this view:GX_CAST_R(_OGLView*, m_OSWin)];
    if ([GX_CAST_R(UIView*, osWinP) isKindOfClass:[UIWindow class]]) {
        GX_CAST_R(UIWindow*, osWinP).rootViewController=GX_CAST_R(UIViewController*, m_OSWinCtrler);
    }
    else {
        [GX_CAST_R(UIView*, osWinP) addSubview:GX_CAST_R(_OGLView*, m_OSWin)];
    }
#elif defined(GX_OS_MACOSX)
    if ([GX_CAST_R(id, osWinP) isKindOfClass:[NSWindow class]]) {
        m_OSWin=[[_OGLView alloc] initWithDelegate:this frame:GX_CAST_R(NSWindow*, osWinP).contentView.bounds];
        [GX_CAST_R(NSWindow*, osWinP).contentView addSubview:GX_CAST_R(_OGLView*, m_OSWin)];
    }
    else {
        m_OSWin=[[_OGLView alloc] initWithDelegate:this frame:GX_CAST_R(NSView*, osWinP).bounds];
        [GX_CAST_R(NSView*, osWinP) addSubview:GX_CAST_R(_OGLView*, m_OSWin)];
    }
    m_OSWinCtrler=[[_OGLViewController alloc] initWithDelegate:this view:GX_CAST_R(_OGLView*, m_OSWin)];
#elif defined(GX_OS_ANDROID)
	ANativeWindow_acquire(GX_CAST_R(ANativeWindow*, osWinP));
	m_OSWin=GX_CAST_R(ANativeWindow*, osWinP);
	GJavaJNIEnvAutoPtr jniEnv;
	m_OSWinScale=GJavaCAPI::shared()->appGetDefaultWindowScale(jniEnv.get());
#elif defined(GX_OS_QT)
    m_OSWin=new QWindow();
    m_OSWin->setSurfaceType(QWindow::OpenGLSurface);
    GApplication::Delegate* dge = GApplication::sharedDelegate();
    int depth = (int)dge->windowsSuggestedDepth();
    int stencil = (int)dge->windowsSuggestedStencil();
    int samples = (int)dge->windowsSuggestedSamples();
    QSurfaceFormat sf;
    sf.setDepthBufferSize(depth);
    sf.setStencilBufferSize(stencil);
    sf.setSamples(samples);
    m_OSWin->setFormat(sf);
    m_OSWin->create();
    m_Container=QWidget::createWindowContainer(m_OSWin,NULL);

    if(GX_CAST_R(QObject*,m_OSWinP)->inherits("QMainWindow")) {
        GX_CAST_R(QMainWindow*,m_OSWinP)->setCentralWidget(m_Container);
    }
    else {
        QLayout* lt=GX_CAST_R(QWidget*,m_OSWinP)->layout();
        if(!lt) {
            lt=new QHBoxLayout();
            lt->addWidget(m_Container);
            GX_CAST_R(QWidget*,m_OSWinP)->setLayout(lt);
        }
        else {
            lt->addWidget(m_Container);
        }
    }
#endif
    return m_Context.create(this);
}

float GWindow::getWidth()
{
#if defined(GX_OS_WINDOWS)
	RECT rc;
	::GetClientRect(m_OSWin.getHWND(), &rc);
	return GX_CAST_S(float,rc.right - rc.left);
#elif defined(GX_OS_IPHONE)
    return (float)GX_CAST_R(UIView*, m_OSWin).bounds.size.width;
#elif defined(GX_OS_MACOSX)
    return (float)GX_CAST_R(NSView*, m_OSWin).bounds.size.width;
#elif defined(GX_OS_ANDROID)
    return ANativeWindow_getWidth(GX_CAST_R(ANativeWindow*, m_OSWin))/m_OSWinScale;
#elif defined(GX_OS_QT)
    return m_OSWin->geometry().width();
#endif
}
float GWindow::getHeight()
{
#if defined(GX_OS_WINDOWS)
	RECT rc;
	::GetClientRect(m_OSWin.getHWND(), &rc);
	return GX_CAST_S(float, rc.bottom - rc.top);
#elif defined(GX_OS_IPHONE)
    return (float)GX_CAST_R(UIView*, m_OSWin).bounds.size.height;
#elif defined(GX_OS_MACOSX)
    return (float)GX_CAST_R(NSView*, m_OSWin).bounds.size.height;
#elif defined(GX_OS_ANDROID)
	return ANativeWindow_getHeight(GX_CAST_R(ANativeWindow*, m_OSWin))/m_OSWinScale;
#elif defined(GX_OS_QT)
    return m_OSWin->geometry().width();
#endif
}
float GWindow::getScale()
{
#if defined(GX_OS_WINDOWS)
	return 1.0f;
#elif defined(GX_OS_IPHONE)
    return (float)GX_CAST_R(UIView*, m_OSWin).contentScaleFactor;
#elif defined(GX_OS_MACOSX)
    return (float)GX_CAST_R(NSView*, m_OSWin).window.backingScaleFactor;
#elif defined(GX_OS_ANDROID)
	return m_OSWinScale;
#elif defined(GX_OS_QT)
    return (float)m_OSWin->devicePixelRatio();
#endif
}



void GWindow::idle()
{
}


#include "GXMath.h"
#include "GDataBuffer.h"
#include "GVector.h"

void GWindow::render()
{
	m_Context.setViewport(0.0f, 0.0f, getWidth(), getHeight());

	GPainter& painter = m_Context.getPainter();

	painter.enable3D(getWidth(), getHeight(), GX_PI / 3, 0.1f, 1000.0f);
	painter.lookAt(0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	GSRGraphics* graph = m_Context.getSRGraphics(GSRGraphics::ID_ColorMul);

	static GDataBuffer* data = NULL;
	if (!data) {
		data = GDataBuffer::alloc();

		GVector3 pos[3];

		pos[0].set(-100.0f, -100.0f, 0.0f);
		pos[1].set(100.0f, -100.0f, 0.0f);
		pos[2].set(0.0f, 100.0f, 0.0f);
		
		data->changeBytes(sizeof(pos));
		void* p = data->map();
		memcpy(p, pos, sizeof(pos));
		data->unmap();
	}

	graph->draw(painter, data, GSRGraphics::ITFloat, GX_TRIANGLES, 0, 3);


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


void GWindow::eventResize()
{
    float nw=getWidth();
    float nh=getHeight();
    float s=getScale();
    
    m_Context.resize(nw*s, nh*s);
}

