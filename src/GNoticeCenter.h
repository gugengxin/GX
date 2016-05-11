#pragma once

#include "GXPrefix.h"
#include "GMap.h"
#include "GArray.h"
#include "GObserver.h"
#include "GNotice.h"

class GNoticeCenter {
	friend class GThread;
private:
	class Observer : public GObject {
		GX_OBJECT(Observer);
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
		void removeObs(GObserver* obs);
		void removeObs(GObject* target, GX::Selector sel);
		void removeObs(GObject* target);
		void removeObs(GX::Callback cbk);
	private:
		GObject* m_Key;
		GArray<GObserver> m_Observers;
	};
public:
	static GNoticeCenter* current();
private:
	GNoticeCenter();
	~GNoticeCenter();
public:
	void addObserver(GObject* key,GObserver* obs);
	void removeObserver(GObserver* obs);
	void removeObserver(GObject* target,GX::Selector sel);
	void removeObserver(GObject* target);
	void removeObserver(GX::Callback cbk);
	void postNotice(GNotice* note);

private:
	GMap<GObject, Observer> m_Observers;
};

