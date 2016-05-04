//
//  GDataString.h
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GDataString_h
#define GDataString_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GOWHash.h"
#include "GData.h"



namespace GX {
    template <typename T> gint strlen(const T* v)
    {
        gint res=0;
        while (*v) {
            res++;
            v++;
        }
        return res;
    }
}

template <typename T>
class GDataString : public GObject {
    GX_OBJECT(GDataString);
public:
    inline gint getLength() {
        return m_Length;
    }
    virtual guint getHash() {
        if (m_OWHash.codeA==0) {
            m_OWHash=GOWHash::compute(getDataPtr());
        }
        return m_OWHash.codeA;
    }
    virtual bool isEqual(GObject* obj) {
        if (obj->isKindOfClass(GDataString<T>::gclass)) {
            if (getHash()==obj->getHash()) {
                
                return m_OWHash.codeB==GX_CAST_R(GDataString<T>*, obj)->m_OWHash.codeB &&
                    m_OWHash.codeC==GX_CAST_R(GDataString<T>*, obj)->m_OWHash.codeC;
            }
        }
        return false;
    }
    
    void set(const T* v,gint len=-1)
    {
        if (len<0) {
            len=GX::strlen(v);
        }
        if (changeCapability(len+1)) {
            memcpy(getDataPtr(), v, len*sizeof(T));
            setLength(len);
        }
    }
    void append(const T* v,gint len=-1)
    {
        if (len<0) {
            len=GX::strlen(v);
        }
        if (changeCapability(getLength()+len+1)) {
            memcpy(getDataPtr(getLength()), v, len*sizeof(T));
            setLength(getLength()+len);
        }
    }
    
    void clear() {
        if(changeCapability(0)) {
            setLength(0);
        }
    }
    
protected:
    inline T* getDataPtr() {
        return GX_CAST_R(T*, m_Data.getPtr());
    }
    inline T* getDataPtr(gint idx) {
        return &GX_CAST_R(T*, m_Data.getPtr())[idx];
    }
    bool changeCapability(gint count) {
        count=(count+32-1)/32;
        return m_Data.changeBytes(GX_CAST_S(guint, count)*sizeof(T));
    }
    void setLength(gint v) {
        if (getDataPtr()) {
            getDataPtr()[v]=0;
        }
        m_Length=v;
        m_OWHash.codeA=0;
    }
private:
    GData           m_Data;
    gint            m_Length;
    GOWHash::Code   m_OWHash;
};


GX_OBJECT_TEMPLATE_IMPLEMENT(typename T, GDataString<T>, GObject);

template <typename T>
GDataString<T>::GDataString()
{
    m_Length=0;
    m_OWHash.codeA=0;
    m_OWHash.codeB=0;
    m_OWHash.codeC=0;
}

template <typename T>
GDataString<T>::~GDataString()
{
    
}


#endif /* GDataString_h */
