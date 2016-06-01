//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GXDIRECTX_H
#define AS_GXDIRECTX_H

#include "GXPrefix.h"
#if defined(GX_DIRECTX)

#include <d3d10.h>
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace GX {
	ID3D10Device* D3DDevice();
}

#define GX_POINTS			D3D10_PRIMITIVE_TOPOLOGY_POINTLIST
#define GX_LINES			D3D10_PRIMITIVE_TOPOLOGY_LINELIST
#define GX_LINE_STRIP		D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP
#define GX_TRIANGLES		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST
#define GX_TRIANGLE_STRIP	D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP

#define GX_UINT8			DXGI_FORMAT_R8_UINT
#define GX_UINT16			DXGI_FORMAT_R16_UINT

#endif
#endif //AS_GXDIRECTX_H
