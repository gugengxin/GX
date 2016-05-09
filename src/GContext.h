//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GCONTEXT_H
#define AS_GCONTEXT_H

#include "GXPrefix.h"
#if defined(GX_OPENGL)
#include "GOGLContext.h"
#elif defined(GX_DIRECTX)
#include "GD3DContext.h"
#endif

class GContext : public
#if defined(GX_OPENGL)
                 GOGLContext
#elif defined(GX_DIRECTX)
                 GD3DContext
#endif
        {
protected:
    GContext();
    ~GContext();
private:

};


#endif //AS_GCONTEXT_H
