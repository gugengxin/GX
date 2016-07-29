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
    GX_GOBJECT(GTexture);    
private:
    class Node : public GDataList<GTexture*>::Node {
    public:
        Node(GContext* cnt,GTexture* tex);
        virtual ~Node();
        
    private:
#ifdef GX_OPENGL
        GLuint  m_Name;
#elif defined(GX_DIRECTX)
        ID3D10ShaderResourceView*	m_Name;
        ID3D10SamplerState*			m_SamplerState;
#endif
    };
    
public:
    
private:
    GContext* m_Context;
    Node* m_Node;
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
