//
//  GXMemory.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GXMemory.h"


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

}




