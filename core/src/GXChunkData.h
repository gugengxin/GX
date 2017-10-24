//
//  GXChunkData.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GXChunkData_h
#define GXChunkData_h

#include "GXPrefix.h"

namespace GX {
    class ChunkData {
    private:
        class Block {
        public:
            guint8  nextIndex;
            guint32 chunkOffset:24;
        };
        class Chunk {
        public:
            guint8 firstAvailableBlock;
            guint8 blockAvailable;
            Chunk* prev;
            Chunk* next;
        };
        static Chunk* chunkCreate(guint blockSize,guint8 blockCount);
        static void chunkDestroy(Chunk* chunk);
    public:
        ChunkData(guint32 unitSize, guint8 unitCount);
        ~ChunkData();

        void* add();
        void remove(void* p);
        
    private:
        guint32 m_BlockSize;
        guint8  m_BlockCount;
        guint8  m_ChunkEmptyCount;
        Chunk*  m_ChunkFirst;
        Chunk*  m_ChunkAlloc;
    };
}



#endif /* GXChunkData_h */
