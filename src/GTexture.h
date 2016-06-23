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
        GContext* m_Context;
    };
    
public:
    
private:
    Node* m_Node;
#ifdef GX_OPENGL
    GLuint  m_Name;
#elif defined(GX_DIRECTX)
    
#endif
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
