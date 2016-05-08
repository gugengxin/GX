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

class _AppTimerBridge {
public:
    _AppTimerBridge(){}
    ~_AppTimerBridge(){}
    inline void SetTarget(GApplication* v) {
        m_Target=v;
    }
    inline void AppIdle() {
        m_Target->idle();
    }
    inline void AppDidBecomeActive() {
        m_Target->didBecomeActive();
    }
    inline void AppWillResignActive() {
        m_Target->willResignActive();
    }
    inline void AppDidEnterBackground() {
        m_Target->didEnterBackground();
    }
    inline void AppWillEnterForeground() {
        m_Target->willEnterForeground();
    }
    inline void AppWillTerminate() {
        m_Target->willTerminate();
    }
    inline void AppDidReceiveMemoryWarning() {
        m_Target->didReceiveMemoryWarning();
    }
private:
    GApplication* m_Target;
};

@interface _AppTimer : NSObject {
    _AppTimerBridge _delegate;
}
#if defined(GX_OS_IPHONE)
@property (nonatomic,retain) CADisplayLink* displayTimer;
#elif defined(GX_OS_MACOSX)
@property (nonatomic,assign) dispatch_source_t displayTimer;
#endif
@end


@implementation _AppTimer
@synthesize displayTimer=_displayTimer;

- (id)initWithDelegate:(GApplication*)dge
{
    self=[super init];
    if (self) {
        _delegate.SetTarget(dge);
        
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
                _delegate.AppIdle();
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
    _delegate.AppIdle();
}

- (void)noteAppDidBecomeActive:(NSNotification*)note
{
    _delegate.AppDidBecomeActive();
}
- (void)noteAppWillResignActive:(NSNotification*)note
{
    _delegate.AppWillResignActive();
}
- (void)noteAppDidEnterBackground:(NSNotification*)note
{
    _delegate.AppDidEnterBackground();
}
- (void)noteAppWillEnterForeground:(NSNotification*)note
{
    _delegate.AppWillEnterForeground();
}
- (void)noteAppDidReceiveMemoryWarning:(NSNotification*)note
{
    _delegate.AppDidReceiveMemoryWarning();
}

#endif

- (void)noteAppWillTerminate:(NSNotification*)note
{
    _delegate.AppWillTerminate();
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
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)winMsgWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NULL;
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

class AndroidApp {
public:
    AndroidApp() {
        app=NULL;
        sensorManager=NULL;
        accelerometerSensor=NULL;
        sensorEventQueue=NULL;
        animating=0;
    }
    ~AndroidApp() {

    }

    struct android_app*     app;
    ASensorManager*         sensorManager;
    const ASensor*          accelerometerSensor;
    ASensorEventQueue*      sensorEventQueue;
    gint                    animating;
};

static AndroidApp g_ArdApp;


extern "C" {

extern JNIEXPORT void JNICALL Java_com_gxengine_GX_main
		(JNIEnv *, jclass, jint);
void android_main(struct android_app *app) {
	GX::JavaInitNative(app->activity);
	app->userData=GApplication::shared();
	g_ArdApp.app=app;
	g_ArdApp.app->onAppCmd = GApplication::androidHandleCmd;
	g_ArdApp.app->onInputEvent = GApplication::androidHandleInput;

	g_ArdApp.sensorManager = ASensorManager_getInstance();
	g_ArdApp.accelerometerSensor = ASensorManager_getDefaultSensor(g_ArdApp.sensorManager,
																   ASENSOR_TYPE_ACCELEROMETER);
	g_ArdApp.sensorEventQueue = ASensorManager_createEventQueue(g_ArdApp.sensorManager,
																g_ArdApp.app->looper,
																LOOPER_ID_USER, NULL, NULL);
	g_ArdApp.animating = 0;

	//GJavaJNIEnvAutoPtr jniEnv;
	//GJavaCAPI::shared()->appMainNative(jniEnv.get());
	Java_com_gxengine_GX_main(NULL,NULL,GX::JavaLaunchTypeNative);
}
}

void GApplication::androidHandleCmd(struct android_app* androidApp, int32_t cmd)
{
	GApplication* pApp = GX_CAST_R(GApplication*, androidApp->userData);
	switch (cmd) {
		case APP_CMD_INPUT_CHANGED:
			break;
		case APP_CMD_INIT_WINDOW:
			//pApp->AndroidWindowCreated(androidApp->window);
			break;
		case APP_CMD_TERM_WINDOW:
			//pApp->AndroidWindowDestroyed();
			break;
		case APP_CMD_WINDOW_RESIZED:
			break;
		case APP_CMD_WINDOW_REDRAW_NEEDED:
			break;
		case APP_CMD_CONTENT_RECT_CHANGED:
			break;
		case APP_CMD_GAINED_FOCUS:
			break;
		case APP_CMD_LOST_FOCUS:
			break;
		case APP_CMD_CONFIG_CHANGED:
			//pApp->AndroidWindowChanged();
			break;
		case APP_CMD_LOW_MEMORY:
			//pApp->AndroidAppLowMemory();
			break;
		case APP_CMD_START:
			//pApp->AndroidAppStart();
			break;
		case APP_CMD_RESUME:
			//pApp->AndroidAppResume();
			g_ArdApp.animating = 1;
			break;
		case APP_CMD_SAVE_STATE:
			break;
		case APP_CMD_PAUSE:
			g_ArdApp.animating = 0;
			//pApp->AndroidAppPause();
			break;
		case APP_CMD_STOP:
			//pApp->AndroidAppStop();
			break;
		case APP_CMD_DESTROY:
			//pApp->AndroidAppDestroy();
			break;
		default:
			break;
	}
}
int32_t GApplication::androidHandleInput(struct android_app* app, AInputEvent* event)
{

}

#endif




GApplication* GApplication::shared()
{
    static GApplication g_Obj;
    return &g_Obj;
}

void GApplication::main(Delegate* dge)
{
    GApplication* app=shared();
    app->m_Delegate=dge;
    GThread::current()->setMain();
    
#if defined(GX_OS_APPLE)
    [GX_CAST_R(_AppTimer*, app->m_Timer) start];
    app->didFinishLaunching();
#elif defined(GX_OS_WINDOWS)
	app->createWinMsgWndAndStart();
	app->didFinishLaunching();
#elif defined(GX_OS_ANDROID)

	switch (GX::JavaGetLaunchType()) {
		case GX::JavaLaunchTypeNative: {
			gint64 frameTimeLast=0LL;
			while (true) {
				// Read all pending events.
				int ident;
				int events;
				struct android_poll_source *source;

				// If not animating, we will block forever waiting for events.
				// If animating, we loop until all events are read, then continue
				// to draw the next frame of animation.
				while ((ident = ALooper_pollAll(g_ArdApp.animating ? 0 : -1, NULL, &events,
												(void **) &source)) >= 0) {

					// Process this event.
					if (source != NULL) {
						source->process(g_ArdApp.app, source);
					}

					// If a sensor has data, process it now.
					if (ident == LOOPER_ID_USER) {
						if (g_ArdApp.accelerometerSensor != NULL) {
							ASensorEvent event;
							while (ASensorEventQueue_getEvents(g_ArdApp.sensorEventQueue, &event,
															   1) > 0) {
								//得到重力感应数据
							}
						}
					}

					// Check if we are exiting.
					if (g_ArdApp.app->destroyRequested != 0) {
						exit(0);
						return;
					}
				}

				if (g_ArdApp.animating) {
					gint64 frameTime=GSystem::currentTimeMS();
					if(frameTime-frameTimeLast>=1000LL/60LL) {
						frameTimeLast=frameTime;

						app->idle();
					}
				}
			}
		}
			break;
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
#endif
}


GApplication::GApplication()
{
    m_Delegate=NULL;
#if defined(GX_OS_APPLE)
    m_Timer=[[_AppTimer alloc] initWithDelegate:this];
#elif defined(GX_OS_WINDOWS)
	m_TimerID = 0;
#endif
}

GApplication::~GApplication()
{
#if defined(GX_OS_APPLE)
    [GX_CAST_R(_AppTimer*, m_Timer) release];
#elif defined(GX_OS_WINDOWS)
	if (m_TimerID) {
		timeKillEvent(m_TimerID);
	}
#endif
}

void GApplication::idle()
{
	//*
	static int i = 0;
	GX_LOG_P1(PrioDEBUG, "GApplication", "idle:%d ", i++);
	//const gchar* str = "\x41\x42\x43\x48\x65\x6C\x6C\x6F\x21\x20\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x81\xE3\x82\x82\xE3\x81\x97\xE3\x82\x82\xE3\x81\x97\x21\x20\x41\x56\x41\x56\x41\x56\x41";
	const gchar* str = "中文";
	GX_LOG_W(PrioDEBUG, "GApplication", str);
	//*/

	GThread::current()->popARObj(0);
}

void GApplication::didFinishLaunching()
{
}

void GApplication::didBecomeActive()
{
}

void GApplication::willResignActive()
{
}

void GApplication::didEnterBackground()
{
}

void GApplication::willEnterForeground()
{
}

void GApplication::willTerminate()
{
}

void GApplication::didReceiveMemoryWarning()
{
}



