//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GD3DCONTEXT_H
#define AS_GD3DCONTEXT_H

#include "GXPrefix.h"
#if defined(GX_DIRECTX)
#include "GXDirectX.h"

class GWindow;

class GD3DContext {

protected:
    GD3DContext();
    ~GD3DContext();
public:
	bool create(GWindow* win);
	void destroy();
	bool resize(gfloat32 width, gfloat32 height);

	void renderBegin();
	void setViewport(float x, float y, float w, float h);
	void renderEnd();
public:
	void makeCurrent();
	void makeClear();
protected:
	void readyShader();
	void doneShader();
	void readyTexture();
	void doneTexture();

private:
	bool createView(UINT width, UINT height);

private:
	GWindow* m_Window;

	UINT m_Samples;
	UINT m_SampleQuality;

	IDXGISwapChain*			m_SwapChain;
	ID3D10RenderTargetView* m_RenderTargetView;
	ID3D10DepthStencilView* m_DepthStencilView;
	ID3D10RasterizerState*	m_RasterState;
	ID3D10DepthStencilState* m_DepthStencilState;
};

#endif
#endif //AS_GD3DCONTEXT_H
