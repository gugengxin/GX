//
//  GFrameBuffer.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GFrameBuffer_h
#define GFrameBuffer_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GX3DAPI.h"
#include "GXContext.h"
#include "GDataList.h"
#include "GColor.h"
#include "GCanvas.h"

#include "GXGObject.h"
// Down can't include other h file

class GContext;
class GTexture;

class GFrameBuffer : public GCanvas
{
    friend class GContext;
	GX_PRIVATE_GOBJECT(GFrameBuffer);
public:
#if defined(GX_OPENGL)
    typedef GLuint Name;
    typedef GLuint DepthName;
#elif defined(GX_DIRECTX)
    typedef ID3D10RenderTargetView* Name;
    typedef ID3D10DepthStencilView* DepthName;
#elif defined(GX_METAL)
    typedef void* Name;
    typedef void* DepthName;
#endif
    //仅保存，生成和销毁都在Context完成
    class Handle {
        friend class GX_CONTEXT_BASE;
    public:
        Handle();
        ~Handle();
        
        bool isValid();
        inline Name getName() {
            return m_Name;
        }
        inline DepthName getDepthName() {
            return m_DepthName;
        }

    private:
        Name m_Name;
        DepthName m_DepthName;
#if defined(GX_OPENGL)
#elif defined(GX_DIRECTX)
		ID3D10RasterizerState*	m_RasterState;
#elif defined(GX_METAL)
#endif
    };

    //仅保存，生成和销毁都在Context完成
    class Node : public GDataList<Handle>::Node {
        friend class GX_CONTEXT_BASE;
        friend class GContext;
    private:
        Node();
        virtual ~Node();
    public:
        inline bool isValid() {
            return getData().isValid();
        }
        inline GContext* getContext() {
            return m_Context;
        }
        inline GTexture* getTexture() {
            return m_TexTarget;
        }
        float getWidth();
        float getHeight();

    private:
        GContext* m_Context;
		GTexture* m_TexTarget;
        GColor4F  m_BgdColor;
    };
    
public:
    Name getName();
    GTexture* getTexture();
    
    virtual float getWidth();
    virtual float getHeight();
    virtual float getScale();
    
    bool renderCheck();
    void renderBegin();
    void setViewport(float x, float y, float w, float h, float scale);
    void renderEnd();

private:
    inline Node* getNode() {
        return m_Node;
    }
    inline void setNode(Node* v) {
        m_Node=v;
    }
    void config(Node* node);
private:
    Node* m_Node;
    float m_Scale;
#if defined(GX_OPENGL)
    GLuint  m_PreBindName;
    GLint   m_PreViewport[4];
#elif defined(GX_DIRECTX)
    
#elif defined(GX_METAL)
    
#endif
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFrameBuffer_h */
