#pragma once

#include "GXPrefix.h"

class GNoticeCenter
{
	friend class GThread;
public:
	static GNoticeCenter* current();
private:
	GNoticeCenter();
	~GNoticeCenter();
public:

private:

};

