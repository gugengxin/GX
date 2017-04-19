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
#include "GX3DAPIType.h"
#include "GObject.h"
#include "GDataList.h"
#include "GX3DAPI.h"
#include "GDib.h"
#include "GXContext.h"

#include "GXGObject.h"
class GContext;

class GTexture : public GObject {
    GX_VIRTUAL_GOBJECT(GTexture);
public:
#if defined(GX_OPENGL)
    typedef GLuint Name;
#elif defined(GX_DIRECTX)
    typedef ID3D10ShaderResourceView* Name;
#elif defined(GX_METAL)
    typedef void* Name;
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
#if defined(GX_OPENGL)
        
#elif defined(GX_DIRECTX)
        inline ID3D10ShaderResourceView** getNamePtr() {
            return &m_Name;
        }
        inline ID3D10SamplerState* getSamplerState() {
            return m_SamplerState;
        }
		inline ID3D10SamplerState** getSamplerStatePtr() {
			return &m_SamplerState;
		}
#elif defined(GX_METAL)
        inline void* getSamplerState() {
            return m_SamplerState;
        }
#endif
        
	private:
        Name m_Name;
#if defined(GX_OPENGL)
#elif defined(GX_DIRECTX)
		ID3D10SamplerState* m_SamplerState;
#elif defined(GX_METAL)
        void* m_SamplerState;
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
    };
    
public:
    inline Node* getNode() {
        return m_Node;
    }
    Name getName();
    virtual gint32 getWidth()=0;
    virtual gint32 getHeight()=0;
    virtual gint32 getDepth()=0;
    
protected:
    inline void setNode(Node* v) {
        m_Node=v;
    }
private:
    Node* m_Node;
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
