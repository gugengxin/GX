//
//  GData.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GData_h
#define GData_h

#include "GXPrefix.h"
#include "GObject.h"


class GData : public GObject {
    GX_OBJECT(GData);
	friend class GPieceData;
    template <typename,typename> friend class GDataArray;
    template <typename> friend class GDataString;
public:
    static bool galloc(GX_IN_OUT void*& buf,GX_IN guint size,GX_IN guint toSize);
public:
    inline void* getPtr() {
        return m_Buffer;
    }
    inline guint getBytes() {
        return m_Bytes;
    }
    inline bool isStatic() {
        return m_IsStatic;
    }
    
    virtual bool changeBytes(GX_IN guint toSize);
    bool changeBytesIfNeed(GX_IN guint toSize);
    void setStatic(const void* data,guint bytes);
	virtual void freeSelf();
	virtual bool robOther(GX_NONNULL GData* other);
    void zeroSelf();
    
private:
    void* m_Buffer;
#if GX_PTR_32BIT
    guint m_Bytes:31;
#elif GX_PTR_64BIT
    guint m_Bytes:63;
#endif
    guint m_IsStatic:1;
};




#endif /* GData_h */
