﻿//
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
    virtual ~GD3DContext();
public:
	virtual bool create(GWindow* win);
	virtual void destroy();
	bool resize(gfloat32 width, gfloat32 height);

	bool renderCheck();
	void renderBegin();
	void setViewport(float x, float y, float w, float h, float scale);
	void renderEnd();
private:
	bool createView(UINT width, UINT height);
public:
	void makeCurrent();
	void makeClear();
protected:
	void readyShader();
	void doneShader();
	void readyTexture();
	void doneTexture();
protected:
	GDib* loadTexture2DNodeReadyDib(GDib* dib);
	static void loadTexture2DNodeInMT(GObject* obj);
	static void unloadTextureNodeInMT(GObject* obj);
	void unloadTextureNodeForContext(GTexture::Node* node);
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

typedef GD3DContext GContextBase;

#endif
#endif //AS_GD3DCONTEXT_H
