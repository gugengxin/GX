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
#include "GX3DAPI.h"
#include "GDib.h"
#include "GXContext.h"

#include "GXGObject.h"
class GContext;

class GTexture : public GObject {
    GX_GOBJECT(GTexture);
public:

    //仅保存，生成和销毁都在Context完成
	class Handle {
        friend class GX_CONTEXT_BASE;
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
        
#if defined(GX_OPENGL)
        inline GLuint getName() {
            return m_Name;
        }
#elif defined(GX_DIRECTX)
        inline ID3D10ShaderResourceView* getName() {
            return m_Name;
        }
		inline ID3D10ShaderResourceView** getNamePtr() {
			return &m_Name;
		}
#elif defined(GX_METAL)
        inline void* getName() {
            return m_Name;
        }
#endif
        
#if defined(GX_OPENGL)
#elif defined(GX_DIRECTX)
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
    
protected:
    inline void setNode(Node* v) {
        m_Node=v;
    }
private:
    Node* m_Node;
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
