#include "GSRGraphics.h"
#include "GSRGraphics.gxsl"
#include "GContext.h"
#include "GMatrix.h"
#include "GColor.h"
#include "GXMath.h"



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
		gx_Position = mul(mvp_mat,layout.position);
#if MI_COLOR || MI_CANDCM
		bridge.b_color=layout.color;
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
		gx_FragColor=bridge.b_color;
#elif MI_CANDCM
		gx_FragColor=bridge.b_color*color_mul;
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
	load(g_SrcVS, g_SrcFP, macros);
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
		cbDesc.ByteWidth = sizeof(GColor4F);
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
    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
		setUniformLocation(U_color_mul, "color_mul");
	}
}


typedef void(*InputBeginFunction)(gint idx, GIBuffer* buffer);
typedef void(*InputEndFunction)(gint idx);

static void _InputBFunFloat(gint idx, GIBuffer* buffer)
{
	buffer->readyUse();

    GX_glEnableVertexAttribArray(A_position);
    GX_glVertexAttribPointer(A_position, 3, GL_FLOAT, GL_FALSE, (GLsizei)buffer->getStride(), buffer->getData(0));

	if (idx != GSRGraphics::ID_ColorMul) {
        GX_glEnableVertexAttribArray(A_color);
        GX_glVertexAttribPointer(A_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, (GLsizei)buffer->getStride(), buffer->getData(3 * sizeof(float)));
	}

	buffer->doneUse();
}
static void _InputEFunFloat(gint idx)
{
    GX_glDisableVertexAttribArray(A_position);
	if (idx != GSRGraphics::ID_ColorMul) {
        GX_glDisableVertexAttribArray(A_color);
	}
}

static InputBeginFunction g_InputBFuns[] = {
	_InputBFunFloat,
};
static InputEndFunction g_InputEFuns[] = {
	_InputEFunFloat,
};

#endif


void GSRGraphics::draw(GPainter& painter, GIBuffer* buffer, InputType inputType, gint mode, gint first, gint count)
{
#if defined(GX_DIRECTX)

	ID3D10Device* device = GX::D3DDevice();

	UINT offset = (UINT)buffer->getOffset();
	UINT stride = (UINT)buffer->getStride();
	device->IASetVertexBuffers(0, 1, buffer->getBufferPtr(), &stride, &offset);
	device->IASetPrimitiveTopology((D3D10_PRIMITIVE_TOPOLOGY)mode);
	device->IASetInputLayout(m_Layouts[inputType]);

	ID3D10Buffer* cbToMapped;
	void* pMap;

	cbToMapped = m_ConstBuffers[CB_mvp_mat];
	cbToMapped->Map(D3D10_MAP_WRITE_DISCARD, 0, &pMap);
	const float* mvp = painter.updateMVPMatrix();
	((GMatrix4*)mvp)->transpose();
	memcpy(pMap, mvp, GX_MATRIX_SIZE);
	cbToMapped->Unmap();
	device->VSSetConstantBuffers(0, 1, &cbToMapped);

	cbToMapped = m_ConstBuffers[CB_color_mul];
	cbToMapped->Map(D3D10_MAP_WRITE_DISCARD, 0, &pMap);
	memcpy(pMap, painter.updateColorMul(), sizeof(GColor4F));
	cbToMapped->Unmap();
	device->PSSetConstantBuffers(0, 1, &cbToMapped);

	device->VSSetShader(getVertexShader());
	device->PSSetShader(getPixelShader());

	device->Draw((UINT)count, (UINT)first);

#elif defined(GX_OPENGL)
	useProgram();

	g_InputBFuns[inputType](getIndex0(), buffer);

	setUniformMatrix4fv(U_mvp_mat, 1, GL_FALSE, (const GLfloat*)painter.updateMVPMatrix());

	setUniform4fv(U_color_mul, 1, (const GLfloat*)painter.updateColorMul());

    GX_glDrawArrays((GLenum)mode, (GLint)first, (GLsizei)count);

	g_InputEFuns[inputType](getIndex0());
#endif
}
