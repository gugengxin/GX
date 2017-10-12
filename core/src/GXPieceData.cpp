//
//  GXPieceData.c
//  GXCore
//
//  Created by gugengxin on 2017/10/10.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "GXPieceData.h"
#include <memory.h>

#if !defined(GX_OS_DESKTOP)
#define GX_PIECE_DATA_PS_DEFAULT 128
#else
#define GX_PIECE_DATA_PS_DEFAULT 256
#endif


namespace GX {

    PieceData::PieceData()
    {
        m_Buffer=NULL;
        m_Bytes=NULL;
        m_PieceSize=GX_PIECE_DATA_PS_DEFAULT;
        m_PieceCount=0;
    }
    PieceData::PieceData(guint32 pieceSize)
    {
        m_Buffer=NULL;
        m_Bytes=NULL;
        m_PieceSize=pieceSize<=0?GX_PIECE_DATA_PS_DEFAULT:pieceSize;
        m_PieceCount=0;
    }
    PieceData::~PieceData()
    {
        if (m_Buffer) {
            GX::gfree(m_Buffer);
        }
    }

    bool PieceData::setPieceSize(guint32 v)
    {
        if (v <= 0) {
            v = GX_PIECE_DATA_PS_DEFAULT;
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
                if (!GX::grealloc(m_Buffer, m_Bytes, toBCount*v)) {
                    return false;
                }
            }
            m_PieceSize = v;
            m_PieceCount = toBCount;
        }
        return true;
    }

    bool PieceData::changeBytes(guint toSize)
    {
        if (toSize == m_Bytes) {
            return true;
        }

        guint32 toBCount = GX_CAST_S(guint32, (toSize + m_PieceSize - 1) / m_PieceSize);
        guint toSizeReal = toBCount*(guint)m_PieceSize;
        if (toBCount > m_PieceCount || toBCount + 1<m_PieceCount) {
            if (!GX::grealloc(m_Buffer, m_PieceSize*(guint)m_PieceCount, toSizeReal)) {
                return false;
            }
        }
        m_Bytes = toSize;
        m_PieceCount = toBCount;
        return true;
    }
    bool PieceData::changeBytesIfNeed(guint toSize)
    {
        if (toSize <= m_Bytes) {
            return true;
        }
        return changeBytes(toSize);
    }

    void PieceData::freeSelf()
    {
        if (m_Buffer) {
            GX::gfree(m_Buffer);
            m_Buffer=NULL;
        }
        m_Bytes=0;
        m_PieceCount = 0;
    }

    void PieceData::zeroSelf()
    {
        GX::gmemset(m_Buffer, 0, m_Bytes);
    }

    
}
