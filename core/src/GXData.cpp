//
//  GXData.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GXData.h"
#include <stdlib.h>
#include <string.h>

namespace GX {
	Data::Data()
	{
		m_Buffer = NULL;
#if GX_PTR_32BIT
		m_Bytes = 0;
#elif GX_PTR_64BIT
		m_Bytes = 0ULL;
#endif
		m_IsStatic = 0;
	}

	Data::~Data()
	{
		if (!m_IsStatic && m_Buffer) {
			::free(m_Buffer);
		}
	}

	bool Data::changeBytes(UNT toSize)
	{
		if (m_IsStatic) {
			return (toSize == m_Bytes);
		}
		else {
			if (toSize == m_Bytes) {
				return true;
			}
		}

#if GX_PTR_32BIT
		if (toSize & 0x80000000) {
			return false;
		}
#elif GX_PTR_64BIT
		if (toSize & 0x8000000000000000ULL) {
			return false;
		}
#endif
		if (GX::grealloc(m_Buffer, m_Bytes, toSize)) {
			m_Bytes = toSize;
			return true;
		}
		return false;
	}

	bool Data::changeBytesIfNeed(UNT toSize)
	{
		if (toSize <= m_Bytes) {
			return true;
		}
		return changeBytes(toSize);
	}

	void Data::setStatic(const void* data, UNT bytes)
	{
		freeSelf();
		m_Buffer = (void*)data;
		m_Bytes = bytes;
		m_IsStatic = 1;
	}

	void Data::freeSelf()
	{
		if (!m_IsStatic && m_Buffer) {
			::free(m_Buffer);
		}
		m_Buffer = NULL;
		m_Bytes = 0;
		m_IsStatic = 0;
	}

	void Data::zeroSelf()
	{
		memset(m_Buffer, 0, m_Bytes);
	}

}


