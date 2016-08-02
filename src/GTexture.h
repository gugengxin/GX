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

class GTexture : public GObject {
#if defined(GX_OPENGL)
    friend class GOGLContext;
#elif defined(GX_DIRECTX)
    friend class GD3DContext;
#endif
    GX_GOBJECT(GTexture);
public:
    class Node : public GDataList<GTexture*>::Node {
#if defined(GX_OPENGL)
        friend class GOGLContext;
#elif defined(GX_DIRECTX)
        friend class GD3DContext;
#endif
        friend class GContext;
    private:
        Node(GContext* cnt);
        virtual ~Node();
    public:
        inline GContext* getContext() {
            return m_Context;
        }
        
    private:
        GContext* m_Context;
#ifdef GX_OPENGL
        GLuint  m_Name;
#elif defined(GX_DIRECTX)
        ID3D10ShaderResourceView*	m_Name;
        ID3D10SamplerState*			m_SamplerState;
#endif
    };
    
public:
    
private:
    inline void setContext(GContext* v) {
        m_Context=v;
    }
    inline void setNode(Node* v) {
        m_Node=v;
    }
private:
    GContext* m_Context;
    Node* m_Node;
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
