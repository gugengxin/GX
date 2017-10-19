//
//  GXStackData.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GXStackData.h"
#include "GXMemory.h"

namespace GX {

    StackData::StackData(guint32 unitSize, guint32 unitCount)
    {
        m_Buffer=NULL;
        m_BufferCache=NULL;
        m_Count=0;
        m_UnitSize=unitSize;
        m_UnitCount=unitCount;
    }

    StackData::~StackData()
    {
        if (m_BufferCache) {
            GX::gfree(m_BufferCache);
        }
        Buffer* p=m_Buffer;
        while (p) {
            Buffer* prev=p->prev;
            GX::gfree(p);
            p=prev;
        }
    }

    bool StackData::push(const void* data)
    {
        if (!m_Buffer || m_Buffer->count>=m_UnitCount) {
            Buffer* p;
            if (m_BufferCache) {
                p=m_BufferCache;
                m_BufferCache=NULL;
                GX::gmemset(p, 0, sizeof(Buffer)+m_UnitSize*m_UnitCount);
            }
            else {
                p=(Buffer*)GX::gcalloc(sizeof(Buffer)+m_UnitSize*m_UnitCount);
                if (!p) {
                    return false;
                }
            }
            p->prev=m_Buffer;
            m_Buffer=p;
        }

        void* dataTo= GX_CAST_R(guint8*, m_Buffer+1)+m_Buffer->count*m_UnitSize;
        GX::gmemcpy(dataTo, data, m_UnitSize);
        m_Buffer->count++;
        m_Count++;
        return true;
    }
    bool StackData::pop()
    {
        if (!m_Buffer) {
            return false;
        }
        m_Buffer->count--;
        m_Count--;
        if (m_Buffer->count<=0) {
            if (m_BufferCache) {
                GX::gfree(m_BufferCache);
            }
            m_BufferCache=m_Buffer;
            m_Buffer=m_Buffer->prev;
        }
        return true;
    }
    bool StackData::pop(void* dataOut)
    {
        if (!m_Buffer) {
            return false;
        }
        m_Buffer->count--;
        m_Count--;
        if (dataOut) {
            void* dataFrom= GX_CAST_R(guint8*, m_Buffer+1)+m_Buffer->count*m_UnitSize;
            GX::gmemcpy(dataOut, dataFrom, m_UnitSize);
        }
        if (m_Buffer->count<=0) {
            if (m_BufferCache) {
                GX::gfree(m_BufferCache);
            }
            m_BufferCache=m_Buffer;
            m_Buffer=m_Buffer->prev;
        }
        return true;
    }
    bool StackData::pop(guint count)
    {
        for (guint i=0; i<count; i++) {
            if(!pop()) {
                return false;
            }
        }
        return true;
    }

    bool StackData::popTo(guint index)
    {
        while (m_Count>index+1) {
            if (!pop()) {
                return false;
            }
        }
        return true;
    }
    bool StackData::popAll()
    {
        while (m_Count>0) {
            if (!pop()) {
                return false;
            }
        }
        return true;
    }

    const void* StackData::top() const
    {
        if (!m_Buffer) {
            return NULL;
        }
        return GX_CAST_R(guint8*, m_Buffer+1)+(m_Buffer->count-1)*m_UnitSize;
    }

    const void* StackData::top(guint index) const
    {
        if (index>=m_Count || !m_Buffer) {
            return NULL;
        }

        guint i=0;
        Buffer* p=m_Buffer;
        while (index-i>=p->count) {
            i+=p->count;
            p=p->prev;
        }
        return GX_CAST_R(guint8*, p+1)+(p->count-(index-i)-1)*m_UnitSize;
    }

}

