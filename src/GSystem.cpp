#include "GSystem.h"
#if defined(GX_OS_ANDROID)
#include "GJavaCAPI.h"
#include "time.h"
#elif defined(GX_OS_APPLE)
#import <Foundation/Foundation.h>
#include <sys/time.h>
#include <mach/mach_time.h>
#elif defined(GX_OS_WINDOWS)
#include <sys/timeb.h>
#include <Windows.h>
#endif

gint64 GSystem::currentTimeMS()
{
#if defined(GX_OS_ANDROID)
    struct timespec now;
    clock_gettime(CLOCK_REALTIME,&now);
    return now.tv_sec*1000 + now.tv_nsec/1000000;
#elif defined(GX_OS_APPLE)
    struct timeval now;
    gettimeofday(&now,NULL);
    return now.tv_sec*1000+now.tv_usec/1000;
#elif defined(GX_OS_WINDOWS)
    struct _timeb tb;
	_ftime_s(&tb);
    return tb.time*1000LL+tb.millitm;
#endif
}


#if defined(GX_OS_WINDOWS)
static double GetPerformanceFrequency()
{
    __int64 res;
    QueryPerformanceFrequency((LARGE_INTEGER*)&res);
    return (double)res;
}
#endif

gint64 GSystem::tickCountNS()
{
#if defined(GX_OS_ANDROID)
    struct timespec now;
    clock_gettime(CLOCK_REALTIME,&now);
    return now.tv_sec*1000000000L + now.tv_nsec;
#elif defined(GX_OS_APPLE)
    static double conversion = 0.0;
    if( conversion == 0.0 )
    {
        mach_timebase_info_data_t info;
        kern_return_t err = mach_timebase_info( &info );
        
        if( err == 0  )
            conversion = (double) info.numer / (double) info.denom;
        else
            conversion = 1.0;
    }
    return GX_CAST_S(gint64, conversion * mach_absolute_time());
#elif defined(GX_OS_WINDOWS)
    static double Frequency=GetPerformanceFrequency();
    __int64 res;
    QueryPerformanceCounter((LARGE_INTEGER*)&res);
    return GX_CAST_S(gint64,((double)res/Frequency)*1000000000.0);
#endif
}