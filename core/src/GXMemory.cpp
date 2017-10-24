//
//  GXMemory.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GXMemory.h"
#include <memory.h>
#include <stdlib.h>

namespace GX {

    void* gmalloc(guint size)
    {
        return ::malloc(size);
    }
    void* gcalloc(guint size)
    {
        return ::calloc(1, size);
    }
    void gfree(void* buf)
    {
        ::free(buf);
    }
    bool grealloc(void*& buf, guint size, guint toSize)
    {
        if (toSize <= 0) {
            if (buf) {
                ::free(buf);
                buf = NULL;
            }
        }
        else if (buf) {
            if (size != toSize) {
                void* p = ::realloc(buf, toSize);
                if (p) {
                    buf = p;
                }
                else {
                    return false;
                }
            }
        }
        else {
            buf = ::malloc(toSize);
            return buf != NULL;
        }
        return true;
    }

    void* gmemset(void* buf, gint32 v, guint len)
    {
        return memset(buf, v, len);
    }

    gint32 gmemcmp(const void *buf1, const void *buf2, guint len)
    {
        return memcmp(buf1, buf2, len);
    }
    void* gmemcpy(void *dst, const void *src, guint len)
    {
        return memcpy(dst, src, len);
    }
    void* gmemmove(void *dst, const void *src, guint len)
    {
        return memmove(dst, src, len);
    }

}




