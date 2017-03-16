
#ifndef GXFILE_h
#define GXFILE_h

#include "GXPrefix.h"

#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
#include <tchar.h>
#include <wchar.h>
#endif

namespace GX {

	inline FILE* fopen(const gtchar* path, const gtchar* mode) 
	{
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
		FILE* res = NULL;
		if (_tfopen_s(&res, path, mode) == 0) {
			return res;
		}
		return NULL;
#else
		return ::fopen(path,mode);
#endif
	}

	inline gint ftell(FILE* fp)
	{
#if (defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)) && GX_PTR_64BIT
		return (gint)_ftelli64(fp);
#else
		return (gint)::ftell(fp);
#endif
	}

	inline bool fseek(FILE* fp, gint offset, int origin)
	{
#if (defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)) && GX_PTR_64BIT
		return _fseeki64(fp,offset,origin)==0;
#else
		return ::fseek(fp,offset,origin)==0;
#endif
	}

}

#endif /* GXFILE_h */
