//
//  GDataStack.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GDataStack_h
#define GDataStack_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GXStackData.h"



#include "GXGObject.h"
// Down can't include other h file

class GDataStackBase : public GObject {
	GX_GOBJECT(GDataStackBase);
};

template <typename T, guint32 N>
class GDataStack : public GDataStackBase {
    friend class GThread;
    GX_GOBJECT(GDataStack);
public:
    bool push(const T& v) {
        return m_Data.push(&v);
    }
    bool pop(T* v) {
        return m_Data.pop(v);
    }
    bool pop() {
        return m_Data.pop();
    }

    gint getCount() const {
        return GX_CAST_S(gint, m_Data.getCount());
    }
    
private:
    GX::StackData m_Data;
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA guint32 N, GDataStack<T GX_COMMA N>, GDataStackBase);

template <typename T, guint32 N>
GDataStack<T,N>::GDataStack() : m_Data(GX_CAST_S(guint32, sizeof(T)),N)
{
}

template <typename T, guint32 N>
GDataStack<T,N>::~GDataStack()
{
}

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GDataStack_h */
