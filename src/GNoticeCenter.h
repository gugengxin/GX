#pragma once

#include "GXPrefix.h"
#include "GMap.h"

class GNoticeCenter {
	friend class GThread;
private:
	class Observer : public GObject {
		GX_OBJECT(Observer);
	public:

	private:

	};
public:
	static GNoticeCenter* current();
private:
	GNoticeCenter();
	~GNoticeCenter();
public:

private:
	GMap<GObject, Observer> m_Observers;
};

