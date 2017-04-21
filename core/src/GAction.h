#ifndef GAction_h
#define GAction_h

#include "GXPrefix.h"
#include "GObject.h"

#include "GXGObject.h"

class GAction : public GObject {
    GX_GOBJECT(GAction);
public:
	inline GObject* getTarget() {
		return m_Target;
	}
	inline GX::Selector getSelector() {
		return m_Action.sel;
	}
	inline GX::Callback getCallback() {
		return m_Action.cbk;
	}
	inline GObject* getObj() {
		return m_Obj;
	}

	void set(GObject* target, GX::Selector sel, GObject* obj);
	void set(GX::Callback cbk, GObject* obj);
	void run();
    void run(GObject* obj);
private:
	GObject* m_Target;
	union {
		GX::Selector sel;
		GX::Callback cbk;
	} m_Action;
	GObject* m_Obj;
};

#include "GXGObjectUD.h"

#endif