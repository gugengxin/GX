//
//  GXStackData.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GXStackData_h
#define GXStackData_h

#include "GXPrefix.h"

namespace GX {

    class StackData {
    public:
        StackData(guint32 unitSize, guint32 unitCount);
        ~StackData();

        bool push(const void* data);
        bool pop();
        bool pop(void* dataOut);
        bool pop(guint count);
        bool popTo(guint index);
        bool popAll();
        const void* top() const;
        const void* top(guint index) const;
        inline guint getCount() const {
            return m_Count;
        }


    private:
        class Buffer {
        public:
            Buffer* prev;
            guint count;
        };
    private:
        Buffer* m_Buffer;
        Buffer* m_BufferCache;
        guint   m_Count;
        guint32 m_UnitSize;
        guint32 m_UnitCount;
    };

}

#endif /* GXStackData_h */
