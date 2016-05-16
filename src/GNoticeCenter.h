﻿#pragma once

#include "GXPrefix.h"
#include "GMap.h"
#include "GArray.h"
#include "GObserver.h"
#include "GNotice.h"


class GNCObserver : public GObject {
	friend class GNoticeCenter;
	GX_OBJECT_DECLARE(GNCObserver,private,private);
public:
	inline GObject* getKey() {
		return m_Key;
	}
	void setKey(GObject* v) {
		GO::retain(v);
		GO::release(m_Key);
		m_Key = v;
	}
	void add(GObserver* obs) {
		m_Observers.add(obs);
	}
	gint getObsCount() {
		return m_Observers.getCount();
	}
	GObserver* getObs(gint idx) {
		return m_Observers.get(idx);
	}

	void removeObs(GObject* target, GX::Selector sel);
	void removeObs(GObject* target);
	void removeObs(GX::Callback cbk);
private:
	GObject* m_Key;
	GPDArray<GObserver*> m_Observers;
};



class GNoticeCenter {
	friend class GThread;
public:
	static GNoticeCenter* current();
private:
	GNoticeCenter();
	~GNoticeCenter();
public:
private:
	void addObserver(GObject* key,GObserver* obs);
public:
	void removeObserver(GObject* target,GX::Selector sel);
	void removeObserver(GObject* target);
	void removeObserver(GX::Callback cbk);
	void postNotice(GNotice* note);

private:
	GMap<GObject, GNCObserver> m_Observers;
};

