#include "GSRGraphics.h"
#include "GSRGraphics.gxsl"
#include "GContext.h"
#include "GMatrix.h"
#include "GColor.h"



//#def MI_COLORMUL
//#def MI_COLOR
//#def MI_CANDCM
/*//GX_SL

vs {
	layout {
		high vec4 position:POSITION;
#if MI_COLOR || MI_CANDCM
		lowp vec4 color:COLOR;
#end
	}
	buffer {
		high mat4 mvp_mat;
	}
	bridge {
#if MI_COLOR || MI_CANDCM
		lowp vec4 b_color:COLOR;
#end
	}
	main {
		gx_Position = mvp_mat * position;
#if MI_COLOR || MI_CANDCM
		b_color=color;
#end
	}
}
fp {
	buffer {
#if MI_COLORMUL || MI_CANDCM
		lowp vec4 color_mul;
#end
	}
	main {
#if MI_COLORMUL
		gx_FragColor=color_mul;
#elif MI_COLOR
		gx_FragColor=b_color;
#elif MI_CANDCM
		gx_FragColor=b_color*color_mul;
#end
	}
}
*///GX_SL


GSRGraphics::GSRGraphics(ID srID) :GShaderBase((guint8)srID, 0, 0, 0)
{
	GX_SHADER_INPUT_INIT();

	static Macro g_Macros[] = {
		{ "MI_COLORMUL", NULL },
		{ "MI_COLOR", NULL },
		{ "MI_CANDCM", NULL },
	};
	Macro macros[] = { g_Macros[srID], {NULL,NULL} };
	load(g_SrcVS, g_SrcVSLen, g_SrcFP, g_SrcFPLen, macros);
}


GSRGraphics::~GSRGraphics()
{
	GX_SHADER_INPUT_FINA();
}


#if defined(GX_DIRECTX)

enum {
	CB_mvp_mat,
	CB_color_mul,
};

bool GSRGraphics::createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength)
{
	switch (getIndex0()) {
	case ID_ColorMul:
	{
		D3D10_INPUT_ELEMENT_DESC layouts[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		};
		setInputLayout(ITFloat, device, pShaderBytecodeWithInputSignature, BytecodeLength, layouts, sizeof(layouts) / sizeof(layouts[0]));
	}
	break;
	case ID_Color:
	case ID_CAndCM:
	{
		D3D10_INPUT_ELEMENT_DESC layouts[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		};
		setInputLayout(ITFloat, device, pShaderBytecodeWithInputSignature, BytecodeLength, layouts, sizeof(layouts) / sizeof(layouts[0]));
	}
	break;
	default:
		return false;
	}
	return true;
}
bool GSRGraphics::createConstantBuffer(ID3D10Device* device)
{
	D3D10_BUFFER_DESC cbDesc;
	cbDesc.Usage = D3D10_USAGE_DYNAMIC;
	cbDesc.ByteWidth = sizeof(GMatrix4);
	cbDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;

	setConstantBuffer(CB_mvp_mat, device, &cbDesc, NULL);

	if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
		cbDesc.Usage = D3D10_USAGE_DYNAMIC;
		cbDesc.ByteWidth = sizeof(GColor4);
		cbDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;

		setConstantBuffer(CB_color_mul, device, &cbDesc, NULL);
	}

	return true;
}

#elif defined(GX_OPENGL)

enum {
	A_position,
	A_color,
};

enum GXShaderU {
	U_mvp_mat,
	U_color_mul,

	UCount,
};

void GSRGraphics::bindAttribLocations()
{
	setAttribLocation(A_position, "position");
	if (getIndex0() == ID_Color || getIndex0() == ID_CAndCM) {
		setAttribLocation(A_color, "color");
	}
}

void GSRGraphics::bindUniformLocations()
{
	setUniformLocation(U_mvp_mat, "mvp_mat");
	if (getIndex0() == ID_Color || getIndex0() == ID_CAndCM) {
		setUniformLocation(U_color_mul, "color_mul");
	}
}

#endif
