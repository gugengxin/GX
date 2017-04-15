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
		inline Name getName() const {
			return m_Name;
		}
		inline DepthName getDepthName() const {
			return m_DepthName;
		}
        inline bool isEnableDepth() {
#if defined(GX_OPENGL)
            return m_DepthName!=0;
#elif defined(GX_DIRECTX) || defined(GX_METAL)
            return m_DepthName!=NULL;
#endif
            
        }
#if defined(GX_OPENGL)
#elif defined(GX_DIRECTX)
		inline ID3D10RasterizerState*	getRasterState() const {
			return m_RasterState;
		}
		inline ID3D10DepthStencilState* getDepthStencilState() const {
			return m_DepthStencilState;
		}
#elif defined(GX_METAL)
        inline void* getDepthStencilState() {
            return m_DepthStencilState;
        }
#endif
    private:
        Name m_Name;
        DepthName m_DepthName;
#if defined(GX_OPENGL)
#elif defined(GX_DIRECTX)
		ID3D10RasterizerState*	m_RasterState; 
		ID3D10DepthStencilState* m_DepthStencilState;
#elif defined(GX_METAL)
        void* m_StencilTex;
        void* m_DepthStencilState;
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
        
        const GColor4F& getBackgroundColor() const {
            return m_BgdColor;
        }
        void setBackgroundColor(float r,float g,float b,float a) {
            m_BgdColor.set(r, g, b, a);
        }

    private:
        GContext* m_Context;
		GTexture* m_TexTarget;
        GColor4F  m_BgdColor;
    };
    
public:
    typedef enum _Use {
        UseFor2D=0,
        UseFor3D,
    } Use;
public:
    Name getName();
    GTexture* getTexture();
    
	virtual void enable2D(float width, float height);
	virtual void enable3D(float width, float height, float fovy, float zNear, float zFar);

    virtual float getWidth();
    virtual float getHeight();
    virtual float getScale();
    
    virtual const GColor4F& getBackgroundColor() const;
    virtual void setBackgroundColor(float r,float g,float b,float a);
    
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
#if defined(GX_METAL)
public:
    virtual void* getRenderEncoder() {
        return m_RenderEncoder;
    }
#endif
private:
    Node* m_Node;
    float m_Scale;
#if defined(GX_OPENGL)
    GLuint  m_PreBindName;
    GLint   m_PreViewport[4];
#elif defined(GX_DIRECTX)
	ID3D10RenderTargetView*		m_PreName;
	ID3D10DepthStencilView*		m_PreDepthName;
	ID3D10RasterizerState*		m_PreRasterState;
	ID3D10DepthStencilState*	m_PreDepthStencilState;
	D3D10_VIEWPORT				m_PreViewport;
#elif defined(GX_METAL)
    void* m_CommandBuffer;
    void* m_RenderEncoder;
#endif
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFrameBuffer_h */
