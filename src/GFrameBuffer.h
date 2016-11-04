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

#include "GXGObject.h"
// Down can't include other h file

class GContext;
class GTexture;

class GFrameBuffer : public GObject
{
	GX_GOBJECT(GFrameBuffer);
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
        Handle() {
#if defined(GX_OPENGL)
            m_Name = 0;
            m_DepthName=0;
#elif defined(GX_DIRECTX)
			m_Name=NULL;
			m_DepthName=NULL;
			m_RasterState=NULL;
#elif defined(GX_METAL)
            m_Name=NULL;
            m_DepthName=NULL;
#endif
        }
        inline bool isValid() {
#if defined(GX_OPENGL)
            return m_Name != 0;
#elif defined(GX_DIRECTX) || defined(GX_METAL)
			return m_Name != NULL;
#endif
        }
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

    private:
        GContext* m_Context;
		GTexture* m_TexTarget;
        GColor4F  m_BgdColor;
    };
    
public:
    inline Node* getNode() {
        return m_Node;
    }
    inline Name getName() {
        if (m_Node) {
            return m_Node->getData().getName();
        }
        return NULL;
    }

protected:
    inline void setNode(Node* v) {
        m_Node=v;
    }
private:
    Node* m_Node;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFrameBuffer_h */
