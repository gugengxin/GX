//
// Created by Gengxin Gu on 16/5/9.
//

#include "GXDirectX.h"
#if defined(GX_DIRECTX)

namespace GX {
	static ID3D10Device* g_D3DDevice = NULL;

	ID3D10Device* d3dDevice()
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


	D3DRasterizerStater::D3DRasterizerStater()
	{
		memset(m_RasterStates, 0, sizeof(m_RasterStates));
	}

	D3DRasterizerStater::~D3DRasterizerStater()
	{
		for (gint i = 0; i < _DCullFaceCount; i++) {
			if (m_RasterStates[i]) {
				m_RasterStates[i]->Release();
			}
		}
	}
}






#endif
