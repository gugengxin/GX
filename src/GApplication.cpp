//
//  GApplication.cpp
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GApplication.h"
#if defined(GX_OS_IPHONE)
#import <UIKit/UIKit.h>
#elif defined(GX_OS_MACOSX)
#import <Cocoa/Cocoa.h>
#elif defined(GX_OS_WINDOWS)
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#elif defined(GX_OS_ANDROID)
#include "GJavaClass.h"
#include "GJavaCAPI.h"
#include <android/sensor.h>
#include "GLog.h"
#endif
#include "GThread.h"
#include "GLog.h"
#include "GSystem.h"


#if defined(GX_OS_APPLE)

class _AppBridge {
public:
    _AppBridge(){}
    ~_AppBridge(){}
    inline void SetTarget(GApplication* v) {
        m_Target=v;
    }
    inline void AppIdle() {
        m_Target->idle();
    }
    inline void AppDidBecomeActive() {
        m_Target->eventResume();
    }
    inline void AppWillResignActive() {
        m_Target->eventPause();
    }
    inline void AppDidEnterBackground() {
        m_Target->eventStop();
    }
    inline void AppWillEnterForeground() {
        m_Target->eventStart();
    }
    inline void AppWillTerminate() {
        m_Target->eventDestroy();
    }
    inline void AppDidReceiveMemoryWarning() {
        
    }
private:
    GApplication* m_Target;
};

@interface _AppHelper : NSObject {
    _AppBridge _bridge;
}
#if defined(GX_OS_IPHONE)
@property (nonatomic,retain) CADisplayLink* displayTimer;
#elif defined(GX_OS_MACOSX)
@property (nonatomic,assign) dispatch_source_t displayTimer;
#endif
@end


@implementation _AppHelper
@synthesize displayTimer=_displayTimer;

- (id)initWithDelegate:(GApplication*)dge
{
    self=[super init];
    if (self) {
        _bridge.SetTarget(dge);
        
#if defined(GX_OS_IPHONE)
        NSNotificationCenter* nc=[NSNotificationCenter defaultCenter];
        [nc addObserver:self
               selector:@selector(noteAppDidBecomeActive:)
                   name:UIApplicationDidBecomeActiveNotification
                 object:nil];
        [nc addObserver:self
               selector:@selector(noteAppWillResignActive:)
                   name:UIApplicationWillResignActiveNotification
                 object:nil];
        [nc addObserver:self
               selector:@selector(noteAppDidEnterBackground:)
                   name:UIApplicationDidEnterBackgroundNotification
                 object:nil];
        [nc addObserver:self
               selector:@selector(noteAppWillEnterForeground:)
                   name:UIApplicationWillEnterForegroundNotification
                 object:nil];
        [nc addObserver:self
               selector:@selector(noteAppWillTerminate:)
                   name:UIApplicationWillTerminateNotification
                 object:nil];
        [nc addObserver:self
               selector:@selector(noteAppDidReceiveMemoryWarning:)
                   name:UIApplicationDidReceiveMemoryWarningNotification
                 object:nil];
#elif defined(GX_OS_MACOSX)
        NSNotificationCenter* nc=[NSNotificationCenter defaultCenter];
        [nc addObserver:self
               selector:@selector(noteAppWillTerminate:)
                   name:NSApplicationWillTerminateNotification
                 object:nil];
        
#endif
    }
    return self;
}

- (void)dealloc
{
#if defined(GX_OS_IPHONE)
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_displayTimer release];
#elif defined(GX_OS_MACOSX)
    if (_displayTimer) {
        dispatch_cancel(_displayTimer);
        _displayTimer=NULL;
    }
#endif
    [super dealloc];
}

- (void)start
{
    if (!_displayTimer) {
        
#if defined(GX_OS_IPHONE)
        self.displayTimer=[CADisplayLink displayLinkWithTarget:self selector:@selector(displayTimerFun:)];
        [_displayTimer addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
#elif defined(GX_OS_MACOSX)
        _displayTimer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0,
                                               dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0));
        dispatch_source_set_timer(_displayTimer, DISPATCH_TIME_NOW, (1.0/60.0) * NSEC_PER_SEC, 0);
        dispatch_source_set_event_handler(_displayTimer, ^{
            dispatch_async(dispatch_get_main_queue(), ^{
                _bridge.AppIdle();
            });
        });
        dispatch_resume(_displayTimer);
#endif
    }
}

- (void)stop
{
    if (_displayTimer) {
#if defined(GX_OS_IPHONE)
        [_displayTimer invalidate];
        self.displayTimer=nil;
#elif defined(GX_OS_MACOSX)
        dispatch_cancel(_displayTimer);
        _displayTimer=NULL;
#endif
    }
}

#if defined(GX_OS_IPHONE)

- (void)displayTimerFun:(id)sender
{
    _bridge.AppIdle();
}

- (void)noteAppDidBecomeActive:(NSNotification*)note
{
    _bridge.AppDidBecomeActive();
}
- (void)noteAppWillResignActive:(NSNotification*)note
{
    _bridge.AppWillResignActive();
}
- (void)noteAppDidEnterBackground:(NSNotification*)note
{
    _bridge.AppDidEnterBackground();
}
- (void)noteAppWillEnterForeground:(NSNotification*)note
{
    _bridge.AppWillEnterForeground();
}
- (void)noteAppDidReceiveMemoryWarning:(NSNotification*)note
{
    _bridge.AppDidReceiveMemoryWarning();
}

#endif

- (void)noteAppWillTerminate:(NSNotification*)note
{
    _bridge.AppWillTerminate();
}

@end

#elif defined(GX_OS_WINDOWS)

LRESULT CALLBACK GApplication::winMsgWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_USER:
	{
		GX_CAST_R(GApplication*, lParam)->idle();
	}
	break;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CALLBACK GApplication::winTimerCallBack(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	GApplication* app = GX_CAST_R(GApplication*, dwUser);
	::PostMessage(app->m_MsgWnd.getHWND(), WM_USER, 0, (LPARAM)app);
}

void GApplication::createWinMsgWndAndStart()
{
	WNDCLASS	wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)winMsgWndProc;
	RECT rc = { 0, 0, 1, 1 };
	m_MsgWnd.create(wc, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, rc, NULL);
	m_TimerID = timeSetEvent(1000 / 60, 1000 / 60, winTimerCallBack, (DWORD_PTR)this, TIME_PERIODIC | TIME_KILL_SYNCHRONOUS);
}
void GApplication::destroyWinMsgWnd()
{
	if (m_TimerID) {
		timeKillEvent(m_TimerID);
		m_MsgWnd.destroy();
	}
}

#elif defined(GX_OS_ANDROID)

#endif




GApplication* GApplication::shared()
{
    static GApplication g_Obj;
    return &g_Obj;
}

GApplication::Delegate* GApplication::sharedDelegate()
{
	return shared()->m_Delegate;
}

void GApplication::main(Delegate* dge, InitData* initData)
{
    GApplication* app=shared();
    app->m_Delegate=dge;
	memcpy(&app->m_InitData,initData, sizeof(InitData));

    GThread::current()->setMain();

	app->eventCreate();

#if defined(GX_OS_APPLE)
    app->eventStart();
#if defined(GX_OS_MACOSX)
    app->eventResume();
#endif
#elif defined(GX_OS_WINDOWS)
	app->eventStart();
    app->eventResume();
#elif defined(GX_OS_ANDROID)
	switch (GX::JavaGetLaunchType()) {
		case GX::JavaLaunchTypeActivity: {

		}
			break;
		case GX::JavaLaunchTypeDaydream: {

		}
			break;
		default:
			GX_ASSERT(0);
			break;
	}
#elif defined(GX_OS_QT)
    app->eventStart();
    app->eventResume();
#endif
}


GApplication::GApplication()
#if defined(GX_OS_QT)
        : QObject(NULL)
#endif
{
    m_Delegate=NULL;
#if defined(GX_OS_APPLE)
    m_Helper=[[_AppHelper alloc] initWithDelegate:this];
#elif defined(GX_OS_WINDOWS)
	m_TimerID = 0;
#endif
}

GApplication::~GApplication()
{
	for (gint i = 0; i < m_Windows.getCount(); i++) {
		delete m_Windows.get(i);
	}
	m_Windows.removeAll();
#if defined(GX_OS_APPLE)
    [GX_CAST_R(_AppHelper*, m_Helper) release];
#elif defined(GX_OS_WINDOWS)
	if (m_TimerID) {
		timeKillEvent(m_TimerID);
	}
#endif
}

void GApplication::idle()
{
    /*
	static int i = 0;
	GX_LOG_P1(PrioINFO, "GApplication", "idle:%d ", i++);
	//const gchar* str = "\x41\x42\x43\x48\x65\x6C\x6C\x6F\x21\x20\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x81\xE3\x82\x82\xE3\x81\x97\xE3\x82\x82\xE3\x81\x97\x21\x20\x41\x56\x41\x56\x41\x56\x41";
	const gchar* str = "中文";
	GX_LOG_W(PrioINFO, "GApplication", str);
	//*/
	for (gint i = 0; i < m_Windows.getCount(); i++) {
		GWindow* win = m_Windows.get(i);
		win->idle();
		win->renderIfNeed();
	}
	GRunLoop::current()->run();
}

void GApplication::eventCreate()
{
	m_Delegate->appCreate(this);
}
void GApplication::eventStart()
{
#if defined(GX_OS_APPLE)
    [GX_CAST_R(_AppHelper*, m_Helper) start];
#elif defined(GX_OS_WINDOWS)
    createWinMsgWndAndStart();
#elif defined(GX_OS_QT)
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(idle()));
    m_Timer.start(1000/60);
#endif
	m_Delegate->appStart(this);
}
void GApplication::eventResume()
{
	m_Delegate->appResume(this);

#if defined(GX_OS_APPLE) || defined(GX_OS_WINDOWS) || defined(GX_OS_QT)
    setCanCreateWindow(m_InitData.getOSWindow());
#endif
}
void GApplication::eventPause()
{
	m_Delegate->appPause(this);
}
void GApplication::eventStop()
{
	m_Delegate->appStop(this);
    
#if defined(GX_OS_APPLE)
    [GX_CAST_R(_AppHelper*, m_Helper) stop];
#elif defined(GX_OS_WINDOWS)
	destroyWinMsgWnd();
#elif defined(GX_OS_QT)
    m_Timer.stop();
    disconnect(&m_Timer,SIGNAL(timeout()),this,SLOT(idle()));
#endif
}
void GApplication::eventDestroy()
{
	m_Delegate->appDestroy(this);
}


void GApplication::setCanCreateWindow(void* osWindow)
{
    m_Delegate->appCanCreateWindow(this, osWindow);
}

void GApplication::addWindow(void* osWin)
{
    m_Windows.add(new GWindow(osWin));
}

GWindow *GApplication::firstWindow()
{
    if(m_Windows.getCount()>0) {
        return m_Windows.first();
    }
    return NULL;
}

gint GApplication::getWindowCount()
{
    return m_Windows.getCount();
}

GWindow *GApplication::getWindow(gint idx)
{
    return m_Windows.get(idx);
}

void GApplication::removeWindow(GWindow *win)
{
	for (gint i = 0; i < m_Windows.getCount(); i++) {
        if (win == m_Windows.get(i)) {
			delete win;
			m_Windows.remove(i);
			break;
		}
	}
}
