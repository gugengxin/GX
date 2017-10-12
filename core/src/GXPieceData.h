//
//  GXPieceData.h
//  GXCore
//
//  Created by gugengxin on 2017/10/10.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef GXPieceData_h
#define GXPieceData_h

#include "GXCoder.h"
#include "GXMemory.h"

namespace GX {

    class PieceData {
    public:
        PieceData();
        PieceData(guint32 pieceSize);
        ~PieceData();

        inline void* getPtr() const {
            return m_Buffer;
        }
        inline void* getPtr(guint offset) const {
            return GX_CAST_R(guint8*, m_Buffer) + offset;
        }
        inline guint getBytes() const {
            return m_Bytes;
        }

        bool setPieceSize(guint32 v);
        bool changeBytes(guint toSize);
        bool changeBytesIfNeed(guint toSize);
        void freeSelf();
        void zeroSelf();

    private:
        void*   m_Buffer;
        guint   m_Bytes;
        guint32 m_PieceSize;
        guint32 m_PieceCount;
    };
}

#endif /* GXPieceData_h */
