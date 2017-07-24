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

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GWindow::Canvas,GCanvas);

GWindow::Canvas::Canvas()
{
    m_Window=NULL;
}

GWindow::Canvas::~Canvas()
{
    
}

float GWindow::Canvas::getWidth()
{
    return m_Window->getWidth();
}
float GWindow::Canvas::getHeight()
{
    return m_Window->getHeight();
}
float GWindow::Canvas::getScale()
{
    return m_Window->getScale();
}

const GColor4F& GWindow::Canvas::getBackgroundColor() const
{
    return m_Window->getBackgroundColor();
}
void GWindow::Canvas::setBackgroundColor(float r,float g,float b,float a)
{
    m_Window->setBackgroundColor(r, g, b, a);
}

#if defined(GX_METAL)
void* GWindow::Canvas::metalRenderEncoder()
{
    return m_Window->getContext().getRenderEncoder();
}
gint GWindow::Canvas::metalBlendIndex()
{
    return GX_CAST_S(gint, m_Window->getContext().getBlend());
}
#endif


#if defined(GX_OS_WINDOWS)

static void SetWindowToHWND(HWND hWnd, GWindow* win)
{
#if GX_PTR_64BIT
	::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)win);
#else
	::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)win);
#endif
}
static GWindow* GetWindowFromHWND(HWND hWnd)
{
#if GX_PTR_64BIT
	return (GWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
#else
	return (GWindow*)::GetWindowLongPtr(hWnd, GWL_USERDATA);
#endif
}
static WNDPROC SetWindowProc(HWND hWnd, WNDPROC proc)
{
#if GX_PTR_64BIT
	return (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)proc);
#else
	return (WNDPROC)SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)proc);
#endif
}

static float GetWindowScale(HWND hWnd)
{
	HDC hdc = ::GetDC(hWnd);
	if (hdc)
	{
		int dpiX = ::GetDeviceCaps(hdc, LOGPIXELSX);//每英寸逻辑像素数 水平
		//int dpiY = ::GetDeviceCaps(hdc, LOGPIXELSY);
		//每英寸逻辑像素数 垂直       
		::ReleaseDC(hWnd, hdc);

		return dpiX / 96.0f;
	}
	return 1.0f;
}

LRESULT CALLBACK GWindow::wndProcP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GWindow* win = GetWindowFromHWND(hWnd);
	if (win) {
		WNDPROC preProc=win->m_WndProcP;
		switch (message) {
		case WM_DESTROY:
		{
			win->eventDestroy();
		}
		break;
		case WM_SIZE:
		case WM_SIZING:
		{
			RECT rc;
			::GetClientRect(hWnd, &rc);
			::MoveWindow(win->m_OSWin.getHWND(), 0, 0, rc.right - rc.left, rc.bottom - rc.top, FALSE);
			win->render();
		}
		break;
		default:
			break;
		}
		return CallWindowProc(preProc, hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK GWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GWindow* win = GetWindowFromHWND(hWnd);
	if (win) {
		switch (message) {
		case WM_SIZE:
		case WM_SIZING:
		{
			//GX_LOG_W(PrioDEBUG, "GWindow", "wndProc WM_SIZE");
			win->eventResize();
		}
		break;
		case WM_PAINT:
		{

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
#if defined(GX_METAL)
#import <QuartzCore/QuartzCore.h>
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
    inline void eventDestroy() {
        m_Target->eventDestroy();
    }
    
    
private:
    GWindow* m_Target;
};

@interface _ContextView :
#if defined(GX_OS_IPHONE)
UIView
#elif defined(GX_OS_MACOSX)
NSView
#endif
{
    _WindowBridge _bridge;
#if defined(GX_METAL)
    CAMetalLayer* _metalLayer;
#endif
}

@end

@implementation _ContextView

- (id)initWithDelegate:(GWindow*)dge frame:(CGRect)rc
{
    self = [super initWithFrame:rc];
    if (self) {
        _bridge.setTarget(dge);
#if defined(GX_OS_IPHONE)
        self.opaque          = YES;
        self.backgroundColor = [UIColor blackColor];
#if defined(GX_METAL)
        _metalLayer=(CAMetalLayer*)self.layer;
#elif defined(GX_OPENGL)
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = @{
                                         kEAGLDrawablePropertyRetainedBacking: [NSNumber numberWithBool:NO],
                                         kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8
                                         };
#endif
#if defined(GX_OS_IOS)
        self.multipleTouchEnabled=YES;
#endif
        
#elif defined(GX_OS_MACOSX)
        self.autoresizingMask=NSViewWidthSizable|NSViewHeightSizable;
        
#if defined(GX_METAL)
        self.wantsLayer = YES;
        self.layer = [CAMetalLayer layer];
        _metalLayer=(CAMetalLayer*)self.layer;
#elif defined(GX_OPENGL)
        [self setWantsBestResolutionOpenGLSurface:YES];
#endif
        
        NSNotificationCenter* nc=[NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(noteWindowWillClose:) name:NSWindowWillCloseNotification object:nil];
#endif
        
#if defined(GX_METAL)
        _metalLayer.device          = GX::metalDevice();
        _metalLayer.pixelFormat     = MTLPixelFormatBGRA8Unorm;
        // this is the default but if we wanted to perform compute on the final rendering layer we could set this to no
        _metalLayer.framebufferOnly = YES;
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

#if defined(GX_METAL)
- (CAMetalLayer*)metalLayer
{
    return _metalLayer;
}
#endif

#if defined(GX_OS_IPHONE)

+ (Class)layerClass
{
#if defined(GX_METAL)
    return [CAMetalLayer class];
#elif defined(GX_OPENGL)
    return [CAEAGLLayer class];
#endif
}

- (void)didMoveToWindow
{
    self.contentScaleFactor = self.window.screen.nativeScale;
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

#if defined(GX_METAL)
+ (Class)layerClass
{
    return [CAMetalLayer class];
}
#endif

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
        _bridge.eventDestroy();
    }
}

#endif

@end


@interface _ContextViewController :
#if defined(GX_OS_IPHONE)
UIViewController
#elif defined(GX_OS_MACOSX)
NSViewController
#endif
{
    _WindowBridge _bridge;
}


@end

@implementation _ContextViewController

- (id)initWithDelegate:(GWindow*)dge view:(_ContextView*)vw
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

#if defined(GX_METAL)
void* GWindow::getMetalLayer()
{
    return [GX_CAST_R(_ContextView*, m_OSWin) metalLayer];
}
#endif

#elif defined(GX_OS_ANDROID)

#include "GAndroidApp.h"

void GWindow::androidDestroy()
{
	GX_LOG_W(PrioDEBUG,"GWindow","androidDestroy");
	m_Context.androidDestroy();
	if(m_OSWin) {
		ANativeWindow_release(GX_CAST_R(ANativeWindow*,m_OSWin));
		m_OSWin=NULL;
	}
}
void GWindow::androidRecreate(ANativeWindow* nw)
{
	GX_LOG_W(PrioDEBUG,"GWindow","androidRecreate");
	ANativeWindow_acquire(nw);
	m_OSWin = nw;
	m_OSWinScale = GAndroidApp::shared()->getDefaultWindowScale();
	m_Context.androidRecreate(this);
}

#elif defined(GX_OS_QT)

_GQWindow::_GQWindow()
{
    m_Delegate=NULL;
}

_GQWindow::~_GQWindow()
{
    m_Delegate->eventDestroy();
}

void _GQWindow::resizeEvent(QResizeEvent *)
{
    m_Delegate->eventResize();
}


#endif

GWindow* GWindow::main(void* osWinP,const char* gameClassName)
{
    GWindow* win=new GWindow(osWinP);
    GApplication::shared()->addComponent(win);
    win->startGame(gameClassName);
    return win;
}

GWindow::GWindow(void* osWinP)
{
	m_OSWinP = osWinP;
    m_BgdColor.set(0.0f, 0.0f, 0.0f, 1.0f);
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
	SetWindowToHWND(m_OSWin.getHWND(), this);

	m_WndProcP = SetWindowProc(GX_CAST_R(HWND, m_OSWinP), wndProcP);
	GX_ASSERT(!GetWindowFromHWND(GX_CAST_R(HWND, m_OSWinP)));
	SetWindowToHWND(GX_CAST_R(HWND, m_OSWinP), this);

	::ShowWindow(m_OSWin.getHWND(), SW_SHOW);
	::UpdateWindow(m_OSWin.getHWND());

	m_OSWinScale = GetWindowScale(m_OSWin.getHWND());

#elif defined(GX_OS_IPHONE)
	m_OSWin = [[_ContextView alloc] initWithDelegate:this frame : GX_CAST_R(UIView*, osWinP).bounds];
	m_OSWinCtrler = [[_ContextViewController alloc] initWithDelegate:this view : GX_CAST_R(_ContextView*, m_OSWin)];
	if ([GX_CAST_R(UIView*, osWinP) isKindOfClass:[UIWindow class]]) {
		GX_CAST_R(UIWindow*, osWinP).rootViewController = GX_CAST_R(UIViewController*, m_OSWinCtrler);
	}
	else {
		[GX_CAST_R(UIView*, osWinP) addSubview:GX_CAST_R(_ContextView*, m_OSWin)];
	}
#elif defined(GX_OS_MACOSX)
	if ([GX_CAST_R(id, osWinP) isKindOfClass:[NSWindow class]]) {
		m_OSWin = [[_ContextView alloc] initWithDelegate:this frame : GX_CAST_R(NSWindow*, osWinP).contentView.bounds];
		[GX_CAST_R(NSWindow*, osWinP).contentView addSubview : GX_CAST_R(_ContextView*, m_OSWin)];
	}
	else {
		m_OSWin = [[_ContextView alloc] initWithDelegate:this frame : GX_CAST_R(NSView*, osWinP).bounds];
		[GX_CAST_R(NSView*, osWinP) addSubview:GX_CAST_R(_ContextView*, m_OSWin)];
	}
	m_OSWinCtrler = [[_ContextViewController alloc] initWithDelegate:this view : GX_CAST_R(_ContextView*, m_OSWin)];
#elif defined(GX_OS_ANDROID)
	ANativeWindow_acquire(GX_CAST_R(ANativeWindow*, osWinP));
	m_OSWin = GX_CAST_R(ANativeWindow*, osWinP);
	m_OSWinScale = GAndroidApp::shared()->getDefaultWindowScale();
#elif defined(GX_OS_QT)
	m_OSWin = new _GQWindow();
	m_OSWin->setDelegate(this);
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
	m_Container = QWidget::createWindowContainer(m_OSWin, NULL);

	if (GX_CAST_R(QObject*, m_OSWinP)->inherits("QMainWindow")) {
		GX_CAST_R(QMainWindow*, m_OSWinP)->setCentralWidget(m_Container);
	}
	else {
		QLayout* lt = GX_CAST_R(QWidget*, m_OSWinP)->layout();
		if (!lt) {
			lt = new QHBoxLayout();
			lt->addWidget(m_Container);
			GX_CAST_R(QWidget*, m_OSWinP)->setLayout(lt);
		}
		else {
			lt->addWidget(m_Container);
		}
    }
#endif
	m_Context.create(this);
    m_Canvas=Canvas::alloc();
    
    m_Canvas->setWindow(this);
}	

GWindow::~GWindow()
{
    GO::release(m_Canvas);
    m_Context.destroy();
#if defined(GX_OS_WINDOWS)
	SetWindowToHWND(m_OSWin.getHWND(),NULL);
	SetWindowProc(GX_CAST_R(HWND, m_OSWinP), m_WndProcP);
	SetWindowToHWND(GX_CAST_R(HWND, m_OSWinP), NULL);
#elif defined(GX_OS_APPLE)
    [GX_CAST_R(id, m_OSWin) release];
    [GX_CAST_R(id, m_OSWinCtrler) release];
#elif defined(GX_OS_ANDROID)
	ANativeWindow_release(GX_CAST_R(ANativeWindow*,m_OSWin));
#elif defined(GX_OS_QT)
    //delete m_OSWin;
    //delete m_Container;
#endif
	GO::release(m_Game);
}

void GWindow::startGame(const char* gameClassName)
{
    GClass* gameClass=GClass::findInMap(gameClassName);
    GX_ASSERT(gameClass!=NULL);
    m_Game=GX_CAST_R(GGame*,gameClass->allocObject());
    GX_ASSERT(m_Game->isKindOfClass(GGame::gclass));
    m_Game->m_Window=this;
    m_Game->eventStart();
}

void GWindow::stopGame()
{
    m_Game->eventStop();
    m_Game->m_Window=NULL;
    GO::release(m_Game);
    m_Game=NULL;
}

float GWindow::getWidth()
{
#if defined(GX_OS_WINDOWS)
	RECT rc;
	::GetClientRect(m_OSWin.getHWND(), &rc);
	return GX_CAST_S(float,rc.right - rc.left) / m_OSWinScale;
#elif defined(GX_OS_IPHONE)
    return (float)GX_CAST_R(UIView*, m_OSWin).bounds.size.width;
#elif defined(GX_OS_MACOSX)
    return (float)GX_CAST_R(NSView*, m_OSWin).bounds.size.width;
#elif defined(GX_OS_ANDROID)
    return ANativeWindow_getWidth(GX_CAST_R(ANativeWindow*, m_OSWin))/m_OSWinScale;
#elif defined(GX_OS_QT)
    return m_OSWin->width();
#endif
}
float GWindow::getHeight()
{
#if defined(GX_OS_WINDOWS)
	RECT rc;
	::GetClientRect(m_OSWin.getHWND(), &rc);
	return GX_CAST_S(float, rc.bottom - rc.top) / m_OSWinScale;
#elif defined(GX_OS_IPHONE)
    return (float)GX_CAST_R(UIView*, m_OSWin).bounds.size.height;
#elif defined(GX_OS_MACOSX)
    return (float)GX_CAST_R(NSView*, m_OSWin).bounds.size.height;
#elif defined(GX_OS_ANDROID)
	return ANativeWindow_getHeight(GX_CAST_R(ANativeWindow*, m_OSWin))/m_OSWinScale;
#elif defined(GX_OS_QT)
    return m_OSWin->height();
#endif
}
float GWindow::getScale()
{
#if defined(GX_OS_WINDOWS)
	return m_OSWinScale;
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

const gint GWindow::AppCID=0xABCD;

GWindow* GWindow::first()
{
    return GX_CAST_R(GWindow*, GApplication::shared()->firstComponent(AppCID));
}

gint GWindow::getAppCID()
{
    return AppCID;
}

void GWindow::idle()
{
    m_Game->run();
}


#include "GXMath.h"
#include "GVector.h"
#include "GAppBundle.h"

void GWindow::render()
{
    if(m_Context.renderCheck()) {
        m_Context.renderBegin();
        m_Context.setViewport(0.0f, 0.0f, getWidth(), getHeight(), getScale());
        m_Game->render(m_Canvas);
        m_Context.renderEnd();
    }
}

void GWindow::eventResize()
{
    float nw=getWidth();
    float nh=getHeight();
    float s=getScale();
    
    if(m_Context.resize(nw*s, nh*s)) {
        render();
    }
}

void GWindow::eventDestroy()
{
    stopGame();
    GApplication::shared()->removeComponent(this);
}

