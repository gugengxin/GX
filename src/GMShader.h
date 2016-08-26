//
//  GMShader.h
//  GX
//
//  Created by Gu Gengxin on 16/8/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GMShader_h
#define GMShader_h

#include "GXPrefix.h"
#if defined(GX_METAL)
#include "GXMetal.h"
#include "GShader.h"

class GMShader : public GShader {

protected:
    GMShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
    virtual ~GMShader();
public:


private:
};

typedef GMShader GShaderBase;


#endif

#endif /* GMShader_h */
