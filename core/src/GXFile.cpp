//
//  GXFile.cpp
//  GXCore
//
//  Created by gugengxin on 2017/10/11.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "GXFile.h"
#include <stdio.h>
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
#include <tchar.h>
#include <wchar.h>
#endif


namespace GX {

#define M_FP() GX_CAST_R(FILE*,m_FILE)

    File::File()
    {
        m_FILE=NULL;
    }
    File::~File()
    {
        if (m_FILE) {
            ::fclose(M_FP());
        }
    }

    bool File::open(const gtchar* path, Mode mode)
    {
        static const gtchar* g_ModeStrs[]={
            GX_T("rb"),
            GX_T("wb"),
            GX_T("ab"),
            GX_T("rwb"),
        };
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
        return _tfopen_s(&M_FP(), path, g_ModeStrs[mode]) == 0;
#else
        m_FILE=::fopen(path,g_ModeStrs[mode]);
        return m_FILE!=NULL;
#endif
    }
    void File::close()
    {
        if (m_FILE) {
            ::fclose(M_FP());
            m_FILE=NULL;
        }
    }

    gint File::tell()
    {
#if (defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)) && GX_PTR_64BIT
        return (gint)_ftelli64(M_FP());
#else
        return (gint)::ftell(M_FP());
#endif
    }

    bool File::seek(gint offset, Seek origin)
    {
#if (defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)) && GX_PTR_64BIT
        return _fseeki64(M_FP(),offset,GX_CAST_S(int, origin))==0;
#else
        return ::fseek(M_FP(),offset,GX_CAST_S(int, origin))==0;
#endif
    }

    gint File::read(void* buf, guint len)
    {
        size_t res=fread(buf, 1, len, M_FP());
        if (res>len) {
            return -1;
        }
        return GX_CAST_S(gint, res);
    }

    gint File::write(const void* buf,guint len)
    {
        size_t res=fwrite(buf, 1, len, M_FP());
        if (res>len) {
            return -1;
        }
        return GX_CAST_S(gint, res);
    }


}
