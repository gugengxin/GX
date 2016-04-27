//
//  GPieceData.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GPieceData.h"


#define M_PIECE_SIZE_DEFAULT 256

GX_OBJECT_IMPLEMENT(GPieceData, GData);

GPieceData::GPieceData()
{
	m_PieceSize = M_PIECE_SIZE_DEFAULT;
	m_PieceCount = 0;
}

GPieceData::GPieceData(guint32 pieceSize)
{
	if (pieceSize <= 0) {
		m_PieceSize = M_PIECE_SIZE_DEFAULT;
	}
	else {
		m_PieceSize = pieceSize;
	}
	m_PieceCount = 0;
}

GPieceData::~GPieceData()
{

}

bool GPieceData::setPieceSize(guint32 v)
{
	if (m_IsStatic) {
		return false;
	}

	if (v <= 0) {
		v = M_PIECE_SIZE_DEFAULT;
	}

	if (m_PieceSize == v) {
		return true;
	}
	else if (m_PieceCount <= 0) {
		m_PieceSize = v;
	}
	else {
		guint32 toBCount = (guint32)((m_Bytes + v - 1) / v);
		if (toBCount*v != m_PieceCount*m_PieceSize) {
			if (!GData::galloc(m_Buffer, m_Bytes, toBCount*v)) {
				return false;
			}
		}
		m_PieceSize = v;
		m_PieceCount = toBCount;
	}
	return true;
}


bool GPieceData::changeBytes(guint32 toSize)
{
	if (m_IsStatic) {
		return (toSize == m_Bytes);
	}
	else {
		if (toSize == m_Bytes) {
			return true;
		}
	}

	guint32 toBCount = (toSize + m_PieceSize - 1) / m_PieceSize;
	guint toSizeReal = toBCount*(guint)m_PieceSize;
#if GX_PTR_32BIT
	if (toSizeReal & 0x80000000) {
		return false;
	}
#elif GX_PTR_64BIT
	if (toSizeReal & 0x8000000000000000ULL) {
		return false;
	}
#endif
	if (toBCount != m_PieceCount) {
		if (!GData::galloc(m_Buffer, m_PieceSize*(guint)m_PieceCount, toSizeReal)) {
			return false;
		}
	}
	m_Bytes = toSize;
	m_PieceCount = toBCount;
	return true;
}
void GPieceData::freeSelf()
{
	GData::freeSelf();
	m_PieceCount = 0;
}
bool GPieceData::robOther(GData* other)
{
	if (!GData::robOther(other)) {
		return false;
	}
	if (other->isKindOfClass(GPieceData::gclass)) {
		m_PieceSize = GX_CAST_R(GPieceData*, other)->m_PieceSize;
		m_PieceCount = GX_CAST_R(GPieceData*, other)->m_PieceCount;

		GX_CAST_R(GPieceData*, other)->m_PieceCount = 0;
	}
	else {
		if (!m_IsStatic) {
			guint32 toBCount = (guint32)((m_Bytes + m_PieceSize - 1) / m_PieceSize);
			guint toSizeReal = toBCount*(guint)m_PieceSize;
			if (toSizeReal != m_Bytes) {
				if (!GData::galloc(m_Buffer, m_Bytes, toSizeReal)) {
					return false;
				}
			}
			m_PieceCount = toBCount;
		}
	}
	return true;
}

