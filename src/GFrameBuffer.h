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
#include "GXOpenGL.h"

#include "GDataList.h"


#include "GXGObject.h"
// Down can't include other h file

class GContext;
class GTexture;

//仅保存，生成和销毁都在Context完成
class GFrameBuffer : public GObject
{
	GX_GOBJECT(GFrameBuffer);
public:
    class Handle {
#if defined(GX_OPENGL)
        friend class GOGLContext;
#elif defined(GX_DIRECTX)
        friend class GD3DContext;
#elif defined(GX_METAL)
        friend class GMTLContext;
#endif
    public:
        Handle() {
#if defined(GX_OPENGL)
            m_Name = 0;
            m_DepthName=0;
#elif defined(GX_DIRECTX)
			m_Name=NULL;
			m_DepthName=NULL;
#elif defined(GX_METAL)

#endif
        }
        inline bool isValid() {
#if defined(GX_OPENGL)
            return m_Name != 0;
#elif defined(GX_DIRECTX)
			return m_Name != NULL;
#elif defined(GX_METAL)

#endif
        }

    private:
#if defined(GX_OPENGL)
        GLuint      m_Name;
        GLuint      m_DepthName;
#elif defined(GX_DIRECTX)
		ID3D10RenderTargetView* m_Name;
		ID3D10DepthStencilView* m_DepthName;
#elif defined(GX_METAL)
        
#endif
    };

    class Node : public GDataList<Handle>::Node {
#if defined(GX_OPENGL)
        friend class GOGLContext;
#elif defined(GX_DIRECTX)
        friend class GD3DContext;
#elif defined(GX_METAL)
        friend class GMTLContext;
#endif
        friend class GContext;
    private:
        Node();
        virtual ~Node();
    public:
        inline bool isValid() {
            return getData().isValid();
        }

    private:
        GContext* m_Context;
		GTexture* m_TexTarget;
    };
    
public:
    inline Node* getNode() {
        return m_Node;
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
