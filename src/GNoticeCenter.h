#pragma once

#include "GXPrefix.h"
#include "GMap.h"
#include "GArray.h"
#include "GNotice.h"
#include "GAction.h"

#include "GXGObject.h"

class GNCObserver : public GObject {
	friend class GNoticeCenter;
	GX_GOBJECT_DECLARE(GNCObserver,private,private);
public:
	inline GObject* getKey() {
		return m_Key;
	}
	void setKey(GObject* v) {
		GO::retain(v);
		GO::release(m_Key);
		m_Key = v;
	}
	void add(GAction* obs) {
		m_Observers.add(obs);
	}
	gint getObsCount() {
		return m_Observers.getCount();
	}
	GAction* getObs(gint idx) {
		return m_Observers.get(idx);
	}
	void removeObs(GAction* obs);
	void removeObs(GObject* target, GX::Selector sel);
	void removeObs(GObject* target);
	void removeObs(GX::Callback cbk);
private:
	GObject* m_Key;
	GArray<GAction> m_Observers;
};



class GNoticeCenter {
	friend class GThread;
public:
	static GNoticeCenter* current();
private:
	GNoticeCenter();
	~GNoticeCenter();
public:
	void addObserver(GObject* key,GAction* obs);
	void removeObserver(GAction* obs);
	void removeObserver(GObject* target,GX::Selector sel);
	void removeObserver(GObject* target);
	void removeObserver(GX::Callback cbk);
	void postNotice(GNotice* note);

private:
	GMap<GObject, GNCObserver> m_Observers;
};

#include "GXGObjectUD.h"