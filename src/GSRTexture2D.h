//
//  GSRTexture2D.h
//  GX
//
//  Created by Gu Gengxin on 16/8/7.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GSRTexture2D_h
#define GSRTexture2D_h

#include "GXPrefix.h"
#include "GOShader.h"
#include "GDShader.h"
#include "GMShader.h"
#include "GBuffer.h"
#include "GPainter.h"


class GSRTexture2D : public GShaderBase {
    friend class GContext;
public:
    typedef enum _MaskMode {
        MM_None=0,
        ///////
        MMCount,
    } MaskMode;

    typedef enum _InputType {
        IT_Float_UShort,
        IT_Float_Float,
    } InputType;

private:
    GSRTexture2D(MaskMode mm);
    virtual ~GSRTexture2D();

#if defined(GX_DIRECTX)
    virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
    virtual bool createConstantBuffer(ID3D10Device* device);
#elif defined(GX_OPENGL)
    virtual void bindAttribLocations();
    virtual void bindUniformLocations();
#endif

    GX_SHADER_INPUT(4, 1, 2);
};

#endif /* GSRTexture2D_hpp */
