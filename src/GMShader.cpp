//
//  GMShader.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GMShader.h"
#if defined(GX_METAL)

GMShader::GMShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
GShader(idxA,idxB,idxC,idxD)
{

}


GMShader::~GMShader()
{

}



#endif