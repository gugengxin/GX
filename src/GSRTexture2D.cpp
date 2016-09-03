//
//  GSRTexture2D.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/7.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GSRTexture2D.h"




GSRTexture2D::GSRTexture2D(GContext* ctx,MaskMode mm) : GShaderBase(ctx,(guint8)mm, 0, 0, 0)
{
    GX_SHADER_INPUT_INIT();

}

GSRTexture2D::~GSRTexture2D()
{

    GX_SHADER_INPUT_FINA();
}