//
//  GXData.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GXData_h
#define GXData_h

#include "GXPrefix.h"
#include "GXMemory.h"

namespace GX {
    
	class Data {
	public:
		Data();
		~Data();

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

		bool changeBytes(guint toSize);
		bool changeBytesIfNeed(guint toSize);
		void setStatic(const void* data, guint bytes);
		void freeSelf();
		void zeroSelf();

	private:
		void* m_Buffer;
#if GX_PTR_32BIT
		guint m_Bytes : 31;
#elif GX_PTR_64BIT
		guint m_Bytes : 63;
#endif
		guint m_IsStatic : 1;
	};

}

#endif /* GXData_h */
