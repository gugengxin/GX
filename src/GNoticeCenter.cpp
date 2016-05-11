#include "GNoticeCenter.h"
#include "GThread.h"

GX_OBJECT_IMPLEMENT(GNoticeCenter::Observer, GObject);

GNoticeCenter::Observer::Observer()
{

}

GNoticeCenter::Observer::~Observer()
{

}




GNoticeCenter* current()
{
	return GThread::current()->getNoticeCenter();
}

GNoticeCenter::GNoticeCenter()
{

}


GNoticeCenter::~GNoticeCenter()
{
}
