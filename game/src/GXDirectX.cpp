//
// Created by Gengxin Gu on 16/5/9.
//

#include "GXDirectX.h"
#if defined(GX_DIRECTX)

namespace GX {
	static ID3D10Device* g_D3DDevice = NULL;

	ID3D10Device* direct3DDevice()
	{
		if (!g_D3DDevice) {
			UINT createDeviceFlags = 0;
//#ifdef GX_DEBUG
//			createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
//#endif
			HRESULT hr=D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, D3D10_SDK_VERSION, &g_D3DDevice);
			GX_ASSERT(SUCCEEDED(hr));
		}
		return g_D3DDevice;
	}


	Direct3DCullFacer::Direct3DCullFacer()
	{
		memset(m_RasterStates, 0, sizeof(m_RasterStates));
	}

	Direct3DCullFacer::~Direct3DCullFacer()
	{
		for (gint i = 0; i < _DCullFaceCount; i++) {
			if (m_RasterStates[i]) {
				m_RasterStates[i]->Release();
			}
		}
	}

	void Direct3DCullFacer::setCullFace(DCullFace v)
	{
		DCullFacer::setCullFace(v);

		direct3DCFUpdate();
	}

	void Direct3DCullFacer::direct3DCFUpdate()
	{
		DCullFace cf = getCullFace();

		D3D10_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.FillMode = D3D10_FILL_SOLID;
		desc.CullMode = GX_CAST_S(D3D10_CULL_MODE, cf +1);
		desc.FrontCounterClockwise = TRUE;
		desc.DepthBias = 0;
		desc.DepthBiasClamp = 0.0f;
		desc.SlopeScaledDepthBias = 0.0f;
		desc.DepthClipEnable = TRUE;
		desc.ScissorEnable = FALSE;
		desc.MultisampleEnable = direct3DCFNeedMultisampleEnabled();
		desc.AntialiasedLineEnable = FALSE;

		GX_ASSERT(S_OK == direct3DDevice()->CreateRasterizerState(&desc, &m_RasterStates[cf]));
		g_D3DDevice->RSSetState(m_RasterStates[cf]);
	}

}






#endif
