//
//  GSRTexture2D.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/7.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GSRTexture2D.h"


/*//GX_SL
vs {
	layout {
		high vec4 position:hl_POSITION,m_attribute0;
        medi vec2 texCoord:hl_TEXCOORD,m_attribute1;
	}
	buffer {
		high mat4 mvp_mat;
	}
	bridge {
        medi vec2 b_texCoord:hl_TEXCOORD;
	}
	main {
		gx_Position = mul(buffer.mvp_mat,layout.position);
        bridge.b_texCoord=layout.texCoord;
	}
}
fp {
	buffer {
        lowp vec4 color_mul;
	}
    texture {
        lowp tex2d[0] texBase;
    }
	main {
        gx_FragColor=tex2d(texture.texBase,bridge.b_texCoord)*buffer.color_mul;
	}
}
*///GX_SL



GSRTexture2D::GSRTexture2D(GContext* ctx,MaskMode mm) : GShaderBase(ctx,(guint8)mm, 0, 0, 0)
{
    GX_SHADER_INPUT_INIT();

}

GSRTexture2D::~GSRTexture2D()
{

    GX_SHADER_INPUT_FINA();
}