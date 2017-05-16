#ifndef GNoticeCenter_h
#define GNoticeCenter_h


#include "GXPrefix.h"
#include "GMap.h"
#include "GArray.h"
#include "GNotice.h"
#include "GAction.h"

#include "GXGObject.h"

class GNoticeCenter {
	friend class GThread;
public:
	static GNoticeCenter* current();
private:
    class Observer : public GObject {
        friend class GNoticeCenter;
        GX_GOBJECT(Observer);
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
private:
	GNoticeCenter();
	~GNoticeCenter();
public:
    void addObserver(GObject* key,GAction* obs);
    void addObserver(GObject* key,GObject* target,GX::Selector sel);
    void addObserver(GObject* key,GX::Callback cbk);
	void removeObserver(GAction* obs);
	void removeObserver(GObject* target,GX::Selector sel);
	void removeObserver(GObject* target);
	void removeObserver(GX::Callback cbk);
	void postNotice(GNotice* note);
    void postNotice(GObject* key,GObject* obj);

private:
	GMap<GObject, Observer> m_Observers;
};

#include "GXGObjectUD.h"

#endif
