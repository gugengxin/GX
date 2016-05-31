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



#endif
#endif //AS_GXDIRECTX_H
