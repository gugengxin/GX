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
#include "GCanvas.h"
#include "GTexture2D.h"


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
    
    inline bool isAlphaOnly() {
        return getIndex0()!=0;
    }
    
    inline bool isColorMul() {
        return getIndex1()!=0;
    }
    
    inline MaskMode getMaskMode() {
        return (MaskMode)getIndex2();
    }
    
	void draw(GCanvas* canvas,
		GBuffer* buffer, guint bufOffset, guint bufStride,
		InputType inputType,
		GTexture2D* texBase,
		gint mode, gint first, gint count,
		GTexture2D* texMask);

private:
    GSRTexture2D(GContext* ctx,bool alphaOnly,bool colorMul,MaskMode mm);
    virtual ~GSRTexture2D();

#if defined(GX_OPENGL)
    virtual void bindAttribLocations();
    virtual void bindUniformLocations();
    
    typedef void(*InputBeginFunction)(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm, GBuffer* buffer, guint offset, guint stride);
    typedef void(*InputEndFunction)(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm);
    static void _InputBFunFloat_UShort(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm, GBuffer* buffer, guint offset, guint stride);
    static void _InputEFunFloat_UShort(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm);
    static void _InputBFunFloat_Float(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm, GBuffer* buffer, guint offset, guint stride);
    static void _InputEFunFloat_Float(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm);
    static InputBeginFunction g_InputBFuns[];
    static InputEndFunction g_InputEFuns[];
#elif defined(GX_DIRECTX)
    virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
    virtual bool createConstantBuffer(ID3D10Device* device);
#elif defined(GX_METAL)
    virtual void deployPLState(gint inputType,void* plStateDescriptor);
    virtual void createUniformBuffer(void* device);
#endif

    GX_SHADER_INPUT(4, 2, 2, 2, 2);
};

#endif /* GSRTexture2D_hpp */
