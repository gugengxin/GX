#pragma once

#include "GXPrefix.h"
#include "GObject.h"


class GNotice : public GObject {
	friend class GNoticeCenter;
	GX_OBJECT(GNotice);
public:
	inline GObject* getKey() {
		return m_Key;
	}
	inline GObject* getObj() {
		return m_Obj;
	}
	inline GObject* getObserverObj() {
		return m_ObsObj;
	}
	void setKey(GObject* v);
	void setObj(GObject* v);
private:
	void setObserverObj(GObject* v);
private:
	GObject* m_Key;
	GObject* m_Obj;
	GObject* m_ObsObj;
};

