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
		high vec4 position:hl_POSITION,m_attribute0;
#if MI_COLOR || MI_CANDCM
		lowp vec4 color:hl_COLOR,m_attribute1;
#end
	}
	buffer {
		high mat4 mvp_mat;
	}
	bridge {
#if MI_COLOR || MI_CANDCM
		lowp vec4 b_color:hl_COLOR;
#end
	}
	main {
		gx_Position = mul(buffer.mvp_mat,layout.position);
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
		gx_FragColor=buffer.color_mul;
#elif MI_COLOR
		gx_FragColor=bridge.b_color;
#elif MI_CANDCM
		gx_FragColor=bridge.b_color*buffer.color_mul;
#end
	}
}
*///GX_SL


GSRGraphics* GSRGraphics::shared(ID srID)
{
    static GSRGraphics* g_Shaders[IDCount]={NULL};
    if (!g_Shaders[srID]) {
        ready();
        g_Shaders[srID] = new GSRGraphics(srID);
        done();
    }
    return g_Shaders[srID];
}

GSRGraphics::GSRGraphics(ID srID) : GShaderBase((guint8)srID, 0, 0, 0)
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


#if defined(GX_OPENGL)

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


void GSRGraphics::_InputBFunFloat(gint idx, GBuffer* buffer, guint offset, guint stride)
{
    readyUseBuffer(buffer);

    GX_glEnableVertexAttribArray(A_position);
    GX_glVertexAttribPointer(A_position, 3, GL_FLOAT, GL_FALSE, (GLsizei)stride, getBufferData(buffer, offset));

	if (idx != GSRGraphics::ID_ColorMul) {
        GX_glEnableVertexAttribArray(A_color);
        GX_glVertexAttribPointer(A_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, (GLsizei)stride, getBufferData(buffer, offset+3 * sizeof(float)));
	}

    doneUseBuffer(buffer);
}
void GSRGraphics::_InputEFunFloat(gint idx)
{
    GX_glDisableVertexAttribArray(A_position);
	if (idx != GSRGraphics::ID_ColorMul) {
        GX_glDisableVertexAttribArray(A_color);
	}
}

GSRGraphics::InputBeginFunction GSRGraphics::g_InputBFuns[] = {
	_InputBFunFloat,
};
GSRGraphics::InputEndFunction GSRGraphics::g_InputEFuns[] = {
	_InputEFunFloat,
};

#elif defined(GX_DIRECTX)

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
		setInputLayout(IT_Float, device, pShaderBytecodeWithInputSignature, BytecodeLength, layouts, sizeof(layouts) / sizeof(layouts[0]));
	}
	break;
	case ID_Color:
	case ID_CAndCM:
	{
		D3D10_INPUT_ELEMENT_DESC layouts[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		};
		setInputLayout(IT_Float, device, pShaderBytecodeWithInputSignature, BytecodeLength, layouts, sizeof(layouts) / sizeof(layouts[0]));
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

#elif defined(GX_METAL)

enum {
    UB_mvp_mat,
    UB_color_mul,
};

void GSRGraphics::deployPLState(gint inputType,void* plStateDescriptor)
{
#define M_PSD() GX_CAST_R(MTLRenderPipelineDescriptor*, plStateDescriptor)
    switch (inputType) {
        case IT_Float:
        {
            MTLVertexDescriptor* vd=[[MTLVertexDescriptor alloc] init];
            
            // 设置attributes
            // pos
            vd.attributes[0].format = MTLVertexFormatFloat3;
            vd.attributes[0].bufferIndex = 0;
            vd.attributes[0].offset = 0;
            // color
            if (getIndex0() == ID_Color || getIndex0() == ID_CAndCM) {
                vd.attributes[1].format = MTLVertexFormatUChar4Normalized;
                vd.attributes[1].bufferIndex = 0;
                vd.attributes[1].offset = 3 * sizeof(float);
                
                // 设置layouts
                vd.layouts[0].stride = 3*sizeof(float) + 4*sizeof(unsigned char);
            }
            else {
                // 设置layouts
                vd.layouts[0].stride = 3*sizeof(float);
            }
            vd.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
            vd.layouts[0].stepRate=1;
            
            M_PSD().vertexDescriptor=vd;
            [vd release];
        }
            break;
        default:
            break;
    }
#undef M_PSD
}

void GSRGraphics::createUniformBuffer(void* device)
{
    setUniformBuffer(UB_mvp_mat, device, GX_MATRIX_SIZE);
    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
        setUniformBuffer(UB_color_mul, device, sizeof(GColor4F));
    }
}

#endif


void GSRGraphics::draw(GCanvas* canvas, GBuffer* buffer, guint bufOffset, guint bufStride, InputType inputType, gint mode, gint first, gint count)
{
#if defined(GX_OPENGL)
    
    useProgram();
    
    g_InputBFuns[inputType](getIndex0(), buffer, bufOffset, bufStride);
    
    setUniformMatrix4fv(U_mvp_mat, 1, GL_FALSE, (const GLfloat*)canvas->updateMVPMatrix());

    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
        setUniform4fv(U_color_mul, 1, (const GLfloat*)canvas->updateColorMul());
    }
    GX_glDrawArrays((GLenum)mode, (GLint)first, (GLsizei)count);
    
    g_InputEFuns[inputType](getIndex0());

    unuseProgram();
    
#elif defined(GX_DIRECTX)

	ID3D10Device* device = GX::direct3DDevice();

	UINT offset = (UINT)bufOffset;
	UINT stride = (UINT)bufStride;
	IASetVertexBuffers(device, 0, 1, buffer, &offset, &stride);
	device->IASetPrimitiveTopology((D3D10_PRIMITIVE_TOPOLOGY)mode);
	device->IASetInputLayout(m_Layouts[inputType]);

	ID3D10Buffer* cbToMapped;
	void* pMap;

	cbToMapped = m_ConstBuffers[CB_mvp_mat];
	cbToMapped->Map(D3D10_MAP_WRITE_DISCARD, 0, &pMap);
	const float* mvp = canvas->updateMVPMatrix();
	((GMatrix4*)mvp)->transpose();
	memcpy(pMap, mvp, GX_MATRIX_SIZE);
	cbToMapped->Unmap();
	device->VSSetConstantBuffers(0, 1, &cbToMapped);

    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
        cbToMapped = m_ConstBuffers[CB_color_mul];
        cbToMapped->Map(D3D10_MAP_WRITE_DISCARD, 0, &pMap);
		memcpy(pMap, canvas->updateColorMul(), sizeof(GColor4F));
        cbToMapped->Unmap();
        device->PSSetConstantBuffers(0, 1, &cbToMapped);
    }

	device->VSSetShader(getVertexShader());
	device->PSSetShader(getPixelShader());

	device->Draw((UINT)count, (UINT)first);
    
#elif defined(GX_METAL)
    
    id<MTLRenderCommandEncoder>rce=GX_CAST_R(id<MTLRenderCommandEncoder>, canvas->metalRenderEncoder());
    
    [rce setRenderPipelineState:GX_CAST_R(id<MTLRenderPipelineState>,getPLStates()[inputType*GX::_DBlendCount+canvas->metalBlendIndex()])];
    
    setVertexBuffer(rce, buffer, bufOffset, 0);
    
    void* pMap=[GX_CAST_R(id<MTLBuffer>, getUBuffers()[UB_mvp_mat]) contents];
    const float* mvp = canvas->updateMVPMatrix();
    ((GMatrix4*)mvp)->transpose();
    memcpy(pMap, mvp, GX_MATRIX_SIZE);
    [rce setVertexBuffer:GX_CAST_R(id<MTLBuffer>, getUBuffers()[UB_mvp_mat]) offset:0 atIndex:1];

    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
        pMap=[GX_CAST_R(id<MTLBuffer>, getUBuffers()[UB_color_mul]) contents];
        const float* clrMul = canvas->updateColorMul();
        memcpy(pMap, clrMul, sizeof(GColor4F));
        [rce setFragmentBuffer:GX_CAST_R(id<MTLBuffer>, getUBuffers()[UB_color_mul]) offset:0 atIndex:0];
    }
    
    [rce drawPrimitives:(MTLPrimitiveType)mode vertexStart:(NSUInteger)first vertexCount:(NSUInteger)count];
    
    /*
    [rce setVertexBuffer:nil offset:0 atIndex:0];
    [rce setVertexBuffer:nil offset:0 atIndex:1];
    if (getIndex0() == ID_ColorMul || getIndex0() == ID_CAndCM) {
        [rce setFragmentBuffer:nil offset:0 atIndex:0];
    }
    //*/
#endif
}
