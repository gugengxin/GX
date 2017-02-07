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
#include "GXData.h"
#include "GSerialize.h"

#include "GXGObject.h"

class GData : public GObject, public GSerialize, public GUnserialize {
	friend class GPieceData;
    GX_GOBJECT(GData);
public:
    inline void* getPtr() const {
        return m_Buffer;
    }
	inline void* getPtr(guint offset) const {
		return GX_CAST_R(guint8*, m_Buffer) + offset;
	}
    inline guint getBytes() const {
        return m_Bytes;
    }
    inline bool isStatic() const {
        return m_IsStatic;
    }
    
    virtual bool changeBytes(GX_IN guint toSize);
    bool changeBytesIfNeed(GX_IN guint toSize);
    void setStatic(const void* data,guint bytes);
	virtual void freeSelf();
	virtual bool robOther(GX_NONNULL GData* other);
    void zeroSelf();

protected:
	typedef enum _SKey {
		SKBuf =1,
	} SKey;
protected:
	virtual const GX::UUID& seGetUUID();
	virtual gint seGetBytes();
	virtual gint seEncodeFields(GEncoder& coder);

protected:
	virtual const GX::UUID& ueGetUUID();
	virtual gint ueDecodeField(GDecoder& coder, guint32 key, guint32 len);///返回<0失败 0没有此Key >0成功
    
private:
    void* m_Buffer;
#if GX_PTR_32BIT
    guint m_Bytes:31;
#elif GX_PTR_64BIT
    guint m_Bytes:63;
#endif
    guint m_IsStatic:1;
};

#include "GXGObjectUD.h"

#endif /* GData_h */
