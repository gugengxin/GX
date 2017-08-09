﻿//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GD3DCONTEXT_H
#define AS_GD3DCONTEXT_H

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#if defined(GX_DIRECTX)
#include "GBaseContext.h"
#include "GXDirectX.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"

class GD3DContext : public GBaseContext, public GX::Direct3DCullFacer, public GX::Direct3DBlender {
	friend class GDShader;
protected:
    static void initialize();
protected:
    GD3DContext();
    virtual ~GD3DContext();
protected:
	virtual bool create(GWindow* win);
	virtual void destroy();
	bool resize(gfloat32 width, gfloat32 height);

	bool renderCheck();
	void renderBegin();
	void setViewport(float x, float y, float w, float h, float scale);
	void renderEnd();
private:
	bool createView(UINT width, UINT height);
protected:
	virtual bool direct3DCFNeedMultisampleEnabled();
protected:
	void makeCurrent();
	void makeClear();
protected:
	static void readyShader();
	static void doneShader();
	void readyFrameBuffer();
	void doneFrameBuffer();
protected:
    GX::PixelFormat getPixelFormatForFB() const;
	static void loadFrameBufferNodeInMT(GObject* obj);
	void unloadFrameBufferNodeForContext(GFrameBuffer::Node* node);

private:
	UINT m_Samples;
	UINT m_SampleQuality;

	IDXGISwapChain*			m_SwapChain;
	ID3D10RenderTargetView* m_RenderTargetView;
	ID3D10DepthStencilView* m_DepthStencilView;
	ID3D10DepthStencilState* m_DepthStencilState;
};

#endif
#endif //AS_GD3DCONTEXT_H
