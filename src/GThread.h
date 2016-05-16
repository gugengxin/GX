//
//  GThread.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GThread_h
#define GThread_h

#include "GXPrefix.h"
#include "GXPthread.h"
#include "GObject.h"
#include "GAutoreleasePool.h"
#include "GDataArray.h"
#include "GRunLoop.h"
#include "GNoticeCenter.h"
#include "GAction.h"

class GThread {
    friend class GApplication;
    friend class GAutoreleasePool;
    friend class GObject;
	friend class GRunLoop;
public:

	class Holder : public GObject
	{
		friend class GThread;
		friend class _HelperCreateData;
		GX_OBJECT(Holder);
	public:
		inline GThread* getThread() {
			return m_Thread;
		}

		void detchThread();

	private:
		GX::pthread_t	m_TID;
		GThread*		m_Thread;
	};

public:
    static GThread* main();
    static GThread* current();
	static void sleep(gint ms);

private:
	static void detch(GAction* action);
public:
	static void detch(GObject* target, GX::Selector selector, GObject* obj);
	static void detch(GX::Callback cbk, GObject* obj);

private:
	static Holder* create(GAction* action, bool waitRun);
public:
	static Holder* create(GObject* target, GX::Selector selector, GObject* obj,bool waitRun);
	static Holder* create(GX::Callback cbk, GObject* obj, bool waitRun);

    GRunLoop* getRunLoop();
	GNoticeCenter* getNoticeCenter();
private:
    static void keyCreate();
    static void keyDestory(void* p);
	static void* detchHelper(void*);
	static void* createHelper(void*);
	static void* detchHelperObj(void*);
	static void* detchHelperFun(void*);
	static void* createHelperObj(void*);
	static void* createHelperFun(void*);
    
    GThread();
    ~GThread();
    void setMain();

    void pushARObj(GObject* v);
    void popARObj(gint toCount);
    
private:
	GX::pthread_t m_ID;
    GPDArray<GObject*> m_ARObjs;
    GRunLoop* m_RunLoop;
	GNoticeCenter* m_NoteCenter;
};





#endif /* GThread_h */
