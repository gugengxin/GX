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
#include "GAction.h"

class GRunLoop {
    friend class GThread;
private:
	class Action : public GObject {
		GX_OBJECT(Action);
	public:
		inline GAction* getAction() {
			return m_Action;
		}
		void setAction(GAction* v);
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
		inline void run() {
			m_Action->run();
		}
		void signalIfNeed();
	private:
		GAction*	m_Action;
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
    
	void perform(GAction* action, gint delayMS, bool waitUntilDone);
	void perform(GObject* target, GX::Selector selector, GObject* obj, gint delayMS, bool waitUntilDone);
	void perform(GX::Callback cbk, GObject* obj, gint delayMS, bool waitUntilDone);

	void cancel(GAction* action);
	void cancel(GObject* target, GX::Selector selector);
	void cancel(GObject* target);
	void cancel(GX::Callback cbk);

private:
	GThread* m_Thread;
	GMutex m_Mutex;
	GArray<Action> m_Actions;
	GArray<Action> m_ActsReady;
	GArray<Action> m_ActsRunning;
};





#endif /* GRunLoop_h */
