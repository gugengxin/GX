//
//  GXMemory.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GXMemory_h
#define GXMemory_h

#include "GXPrefix.h"

namespace GX {
    
    void* gmalloc(guint size);
    void* gcalloc(guint size);
    void gfree(void* buf);
    bool grealloc(void*& buf, guint size, guint toSize);

    void* gmemset(void* buf, gint32 v, guint len);
    gint32 gmemcmp(const void *buf1, const void *buf2, guint len);
    void* gmemcpy(void *dst, const void *src, guint len);
    void* gmemmove(void *dst, const void *src, guint len);
    
}

#endif /* GXMemory_h */
