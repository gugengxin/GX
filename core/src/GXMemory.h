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

}





#endif /* GXMemory_h */
