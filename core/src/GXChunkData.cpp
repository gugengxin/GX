//
//  GXChunkData.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GXChunkData.h"
#include "GXMemory.h"


namespace GX {

    ChunkData::Chunk* ChunkData::chunkCreate(guint blockSize,guint8 blockCount)
    {
        guint size=sizeof(Chunk)+blockSize*blockCount;

        Chunk* res=GX_CAST_R(Chunk*, GX::gmalloc(size));
        if (res) {
            res->firstAvailableBlock=0;
            res->blockAvailable=blockCount;
            res->prev=NULL;
            res->next=NULL;

            Block* p=GX_CAST_R(Block*, res+1);
            for (guint i=0; i<GX_CAST_S(guint, blockCount); i++) {
                p->nextIndex=GX_CAST_S(guint8,i+1);
                p->chunkOffset= GX_CAST_S(guint32, GX_CAST_R(guint, p)-GX_CAST_R(guint, res));

                p=GX_CAST_R(Block*, GX_CAST_R(guint8*, p)+blockSize);
            }
        }
        return res;
    }

    void ChunkData::chunkDestroy(Chunk* chunk)
    {
        GX::gfree(chunk);
    }


    ChunkData::ChunkData(guint32 unitSize, guint8 unitCount)
    {
        m_BlockSize=sizeof(Block)+unitSize;
        m_BlockCount=unitCount;
        m_ChunkEmptyCount=0;
        m_ChunkFirst=NULL;
        m_ChunkAlloc=NULL;
    }

    ChunkData::~ChunkData()
    {
        Chunk* p=m_ChunkFirst;
        while (p) {
            Chunk* pTemp=p;
            p=p->next;
            chunkDestroy(pTemp);
        }
    }

    void* ChunkData::add()
    {
        void* res=NULL;

        Chunk* pChunk=m_ChunkAlloc;
        if (!pChunk || !pChunk->blockAvailable) {
            if (!m_ChunkFirst) {
                m_ChunkFirst=chunkCreate(m_BlockSize, m_BlockCount);
                ++m_ChunkEmptyCount;
            }

            pChunk=GX_CAST_R(Chunk*, m_ChunkFirst);
            while (true) {
                if (pChunk->blockAvailable) {
                    break;
                }
                else {
                    if (pChunk->next) {
                        pChunk=pChunk->next;
                    }
                    else {
                        Chunk* pCTemp=chunkCreate(m_BlockSize, m_BlockCount);
                        if(pCTemp) {
                            pChunk->next=pCTemp;
                            pCTemp->prev=pChunk;
                            ++m_ChunkEmptyCount;
                        }
                        else {
                            pChunk=NULL;
                            break;
                        }
                    }
                }
            }
        }

        if (pChunk) {
            m_ChunkAlloc=pChunk;

            if (pChunk->blockAvailable==m_BlockCount) {
                --m_ChunkEmptyCount;
            }

            Block* pBlock=GX_CAST_R(Block*, pChunk+1);
            pBlock=GX_CAST_R(Block*, GX_CAST_R(guint8*, pBlock)+m_BlockSize*pChunk->firstAvailableBlock);
            res=GX_CAST_R(void*, GX_CAST_R(guint8*, pBlock)+sizeof(Block));
            pChunk->firstAvailableBlock=pBlock->nextIndex;
            --pChunk->blockAvailable;
        }

        return res;
    }

    void ChunkData::remove(void* p)
    {
        Block* pBlock=GX_CAST_R(Block*, GX_CAST_R(guint8*, p)-sizeof(Block));
        Chunk* pChunk=GX_CAST_R(Chunk*, GX_CAST_R(guint8*, pBlock)-pBlock->chunkOffset);

        pBlock->nextIndex=pChunk->firstAvailableBlock;
        pChunk->firstAvailableBlock=GX_CAST_S(guint8, (pBlock->chunkOffset-sizeof(Chunk))/m_BlockSize);
        ++pChunk->blockAvailable;

        if (pChunk->blockAvailable==m_BlockCount) {
            ++m_ChunkEmptyCount;
        }

        if (m_ChunkEmptyCount>1) {
            if (pChunk==m_ChunkFirst) {
                m_ChunkFirst=pChunk->next;
                if(pChunk->next) {
                    pChunk->next->prev=NULL;
                }
            }
            else {
                pChunk->prev->next=pChunk->next;
                if(pChunk->next) {
                    pChunk->next->prev=pChunk->prev;
                }
            }
            if(pChunk==m_ChunkAlloc) {
                m_ChunkAlloc=NULL;
            }
            chunkDestroy(pChunk);
            --m_ChunkEmptyCount;
        }
    }
    
}




