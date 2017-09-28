//
//  GXData.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GXData_h
#define GXData_h

#include "GXCoder.h"
#include "GXMemory.h"

namespace GX {
	class Data {
		template <U32> friend class PieceData;
	public:
		Data();
		virtual ~Data();

		inline void* getPtr() const {
			return m_Buffer;
		}
		inline void* getPtr(UNT offset) const {
			return GX_CAST_R(U8*, m_Buffer) + offset;
		}
		inline UNT getBytes() const {
			return m_Bytes;
		}
		inline bool isStatic() const {
			return m_IsStatic;
		}

		virtual bool changeBytes(UNT toSize);
		bool changeBytesIfNeed(UNT toSize);
		void setStatic(const void* data, UNT bytes);
		virtual void freeSelf();
		void zeroSelf();

	private:
		void* m_Buffer;
#if GX_PTR_32BIT
		UNT m_Bytes : 31;
#elif GX_PTR_64BIT
		UNT m_Bytes : 63;
#endif
		UNT m_IsStatic : 1;
	};

	template <U32 PS>
	class PieceData : public Data {
	public:
		PieceData() 
		{
			m_PieceCount = 0;
		}
		virtual ~PieceData() 
		{

		}

		virtual bool changeBytes(UNT toSize) 
		{
			if (m_IsStatic) {
				return (toSize == m_Bytes);
			}
			else {
				if (toSize == m_Bytes) {
					return true;
				}
			}

			U32 toBCount = GX_CAST_S(U32, (toSize + PS - 1) / PS);
			UNT toSizeReal = toBCount*(UNT)PS;
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
				if (!GX::grealloc(m_Buffer, PS*(UNT)m_PieceCount, toSizeReal)) {
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
		U32 m_PieceCount;
	};
#if !defined(GX_OS_DESKTOP)
#define GX_PIECE_DATA_PS_DEFAULT 128
#else
#define GX_PIECE_DATA_PS_DEFAULT 256
#endif

    template <U32 BS>
    class BlockData {
    public:

    private:

    };







}

#endif /* GXData_h */
