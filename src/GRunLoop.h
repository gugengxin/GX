//
//  GRunLoop.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GRunLoop_h
#define GRunLoop_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GMutex.h"
#include "GCondition.h"
#include "GArray.h"

class GRunLoop {
    friend class GThread;
private:
	class Action : public GObject {
		GX_OBJECT(Action);
	public:
		inline GObject* getTarget() {
			return m_Target;
		}
		inline GObject::Selector getSel() {
			return m_Action.sel;
		}
		inline GObject::Fun getFun() {
			return m_Action.fun;
		}
		void set(GObject* target, GObject::Selector sel, GObject* obj);
		void set(GObject::Fun fun, GObject* obj);
		inline gint64 getRunTime() {
			return m_RunTime;
		}
		inline void setRunTime(gint64 v) {
			m_RunTime = v;
		}
		inline void setCond(GCondition* v) {
			m_Cond = v;
		}
		inline bool isCancelled() {
			return m_Cancelled;
		}
		inline void setCancelled() {
			m_Cancelled = true;
		}
		inline bool isDone() {
			return m_Done;
		}
		void run();
		void signalIfNeed();
	private:
		GObject*	m_Target;
		union {
			GObject::Selector sel;
			GObject::Fun fun;
		} m_Action;
		GObject*	m_Obj;
		gint64		m_RunTime;
		GCondition* m_Cond;
		bool		m_Cancelled;
		bool		m_Done;
	};
public:
	static GRunLoop* current();
private:
	GRunLoop(GThread* td);
    ~GRunLoop();
public:
	void run();
    
	void perform(GObject* target, GObject::Selector selector, GObject* obj, gint delayMS, bool waitUntilDone);
	void perform(GObject::Fun fun, GObject* obj, gint delayMS, bool waitUntilDone);
	void cancel(GObject* target, GObject::Selector selector);
	void cancel(GObject* target);
	void cancel(GObject::Fun fun);

private:
	GThread* m_Thread;
	GMutex m_Mutex;
	GArray<Action> m_Actions;
	GArray<Action> m_ActsReady;
	GArray<Action> m_ActsRunning;
};





#endif /* GRunLoop_h */
