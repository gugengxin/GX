//
//  GTexture.h
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GTexture_h
#define GTexture_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GDataList.h"
#include "GXOpenGL.h"
#include "GXDirectX.h"
#include "GDib.h"

#include "GXGObject.h"
class GContext;

//仅保存，生成和销毁都在Context完成
class GTexture : public GObject {
#if defined(GX_OPENGL)
    friend class GOGLContext;
#elif defined(GX_DIRECTX)
    friend class GD3DContext;
#endif
    friend class GContext;
    GX_GOBJECT(GTexture);
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
#elif defined(GX_DIRECTX)
			m_Name = NULL;
			m_SamplerState = NULL;
#elif defined(GX_METAL)
            m_Name=NULL;
            m_SamplerState=NULL;
#endif
		}

		inline bool isValid() {
#if defined(GX_OPENGL)
			return m_Name != 0;
#elif defined(GX_DIRECTX)
			return m_Name != NULL;
#elif defined(GX_METAL)
            return m_Name != NULL;
#endif
		}
	private:
#if defined(GX_OPENGL)
		GLuint  m_Name;
#elif defined(GX_DIRECTX)
		ID3D10ShaderResourceView*	m_Name;
		ID3D10SamplerState*			m_SamplerState;
#elif defined(GX_METAL)
        void*   m_Name;
        void*   m_SamplerState;
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
    };
    
public:
    
private:
    inline void setNode(Node* v) {
        m_Node=v;
    }
private:
    Node* m_Node;
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
