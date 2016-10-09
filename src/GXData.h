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

namespace GX {

	bool galloc(void*& buf, guint size, guint toSize);

	class Data {
		template <guint32> friend class PieceData;
	public:
		Data();
		virtual ~Data();

		inline void* getPtr() {
			return m_Buffer;
		}
		inline void* getPtr(guint offset) {
			return GX_CAST_R(guint8*, m_Buffer) + offset;
		}
		inline guint getBytes() {
			return m_Bytes;
		}
		inline bool isStatic() {
			return m_IsStatic;
		}

		virtual bool changeBytes(GX_IN guint toSize);
		bool changeBytesIfNeed(GX_IN guint toSize);
		void setStatic(const void* data, guint bytes);
		virtual void freeSelf();
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

	template <guint32 PS>
	class PieceData : public Data {
	public:
		PieceData() 
		{
			m_PieceCount = 0;
		}
		virtual ~PieceData() 
		{

		}

		virtual bool changeBytes(guint toSize) 
		{
			if (m_IsStatic) {
				return (toSize == m_Bytes);
			}
			else {
				if (toSize == m_Bytes) {
					return true;
				}
			}

			guint32 toBCount = GX_CAST_S(guint32, (toSize + PS - 1) / PS);
			guint toSizeReal = toBCount*(guint)PS;
#if GX_PTR_32BIT
			if (toSizeReal & 0x80000000) {
				return false;
			}
#elif GX_PTR_64BIT
			if (toSizeReal & 0x8000000000000000ULL) {
				return false;
			}
#endif
			if (toBCount > m_PieceCount || toBCount + 1<m_PieceCount) {
				if (!GX::galloc(m_Buffer, PS*(guint)m_PieceCount, toSizeReal)) {
					return false;
				}
			}
			m_Bytes = toSize;
			m_PieceCount = toBCount;
			return true;
		}
		virtual void freeSelf()
		{
			Data::freeSelf();
			m_PieceCount = 0;
		}

	private:
		guint32 m_PieceCount;
	};
#if defined(GX_OS_MOBILE)
#define GX_PIECE_DATA_PS_DEFAULT 128
#else
#define GX_PIECE_DATA_PS_DEFAULT 256
#endif
}

#endif /* GXData_h */
