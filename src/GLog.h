#pragma once
#include "GXPrefix.h"

class GLog {
public:
	enum Priority {
		PrioUNKNOWN = 0,
		PrioDEFAULT,
		PrioVERBOSE,
		PrioDEBUG,
		PrioINFO,
		PrioWARN,
		PrioERROR,
		PrioFATAL,
		PrioSILENT,
	};

	static void Print(gint prio, const gchar* tag, const gchar* fmt, ...);
	static void Write(gint prio, const gchar* tag, const gchar* msg);
};


#ifdef GX_DEBUG
#define GX_LOG_W(prio,tag,msg)						GLog::Write(GLog::prio,tag,msg)
#define GX_LOG_P1(prio,tag,fmt,p1)					GLog::Print(GLog::prio,tag,fmt,p1)
#define GX_LOG_P2(prio,tag,fmt,p1,p2)				GLog::Print(GLog::prio,tag,fmt,p1,p2)
#define GX_LOG_P3(prio,tag,fmt,p1,p2,p3)			GLog::Print(GLog::prio,tag,fmt,p1,p2,p3)
#define GX_LOG_P4(prio,tag,fmt,p1,p2,p3,p4)			GLog::Print(GLog::prio,tag,fmt,p1,p2,p3,p4)
#define GX_LOG_P5(prio,tag,fmt,p1,p2,p3,p4,p5)		GLog::Print(GLog::prio,tag,fmt,p1,p2,p3,p4,p5)
#define GX_LOG_P6(prio,tag,fmt,p1,p2,p3,p4,p5,p6)	GLog::Print(GLog::prio,tag,fmt,p1,p2,p3,p4,p5,p6)
#else
#define GX_LOG_W(prio,tag,msg)
#define GX_LOG_P1(prio,tag,fmt,p1)
#define GX_LOG_P2(prio,tag,fmt,p1,p2)
#define GX_LOG_P3(prio,tag,fmt,p1,p2,p3)
#define GX_LOG_P4(prio,tag,fmt,p1,p2,p3,p4)
#define GX_LOG_P5(prio,tag,fmt,p1,p2,p3,p4,p5)
#define GX_LOG_P6(prio,tag,fmt,p1,p2,p3,p4,p5,p6)
#endif


