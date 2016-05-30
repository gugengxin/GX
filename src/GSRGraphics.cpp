#include "GSRGraphics.h"
#include "GSRGraphics.gxsl"
#include "GContext.h"



//#def MI_COLORMUL
//#def MI_COLOR
//#def MI_CANDCM
/*//GX_SL

vs {
	layout {
		high vec4 a_position:POSITION;
#if MI_COLOR || MI_CANDCM
		lowp vec4 a_color:COLOR;
#end
	}
	buffer {
		high mat4 u_mvp_mat;
	}
	bridge {
#if MI_COLOR || MI_CANDCM
		lowp vec4 v_color:COLOR;
#end
	}
	main {
		gx_Position = u_mvp_mat * a_position;
#if MI_COLOR || MI_CANDCM
		v_color=a_color;
#end
	}
}
fp {
	buffer {
#if MI_COLORMUL || MI_CANDCM
		lowp vec4 u_color_mul;
#end
	}
	main {
#if MI_COLORMUL
		gx_FragColor=u_color_mul;
#elif MI_COLOR
		gx_FragColor=v_color;
#elif MI_CANDCM
		gx_FragColor=v_color*u_color_mul;
#end
	}
}
*///GX_SL


GSRGraphics::GSRGraphics(ID srID) :GShader((guint8)srID, 0, 0, 0)
{

}


GSRGraphics::~GSRGraphics()
{

}


#if defined(GX_DIRECTX)
bool GSRGraphics::createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength)
{
	return true;
}
bool GSRGraphics::createConstantBuffer(ID3D10Device* device)
{
	return true;
}
#elif defined(GX_OPENGL)

#endif
