#ifndef GArray_h
#define GArray_h

#include "GXPrefix.h"
#include <string.h>
#include "GXData.h"
#include "GObject.h"

#include "GXGObject.h"

class GArrayBase : public GObject
{
	GX_GOBJECT(GArrayBase);
};

template <class T>
class GArray : public GArrayBase {
	friend class GRunLoop;
	friend class GNoticeCenter;
    friend class GResourceManager;
    friend class GFTFont;
	GX_GOBJECT(GArray);
public:
	gint getCount() const {
		return (gint)(m_Data.getBytes() / sizeof(T*));
	}
	T* get(gint index) const {
		return GX_CAST_R(T**, m_Data.getPtr())[index];
	}
    T* first() const {
        if (m_Data.getBytes()>0) {
            return GX_CAST_R(T**, m_Data.getPtr())[0];
        }
        return NULL;
    }
    T* last() const {
        if (m_Data.getBytes()>0) {
            return GX_CAST_R(T**, m_Data.getPtr())[(m_Data.getBytes() / sizeof(T*))-1];
        }
        return NULL;
    }
    
    gint getIndex(const T* v) const {
        gint count=getCount();
        for (gint i=0; i<count; i++) {
            if (v==get(i)) {
                return i;
            }
        }
        return -1;
    }

	bool add(T* v) {
		gint dc = getCount();
		if (changeCount(dc + 1)) {
			GX_CAST_R(T**, m_Data.getPtr())[dc] = v;
			GO::retain(v);
			return true;
		}
		return false;
	}
	bool add(GArray<T>* arr) {
		gint dc = getCount();
		if (changeCount(dc + arr->getCount())) {
			for (gint i = 0; i < arr->getCount(); i++) {
				T* v = arr->get(i);
				GX_CAST_R(T**, m_Data.getPtr())[dc] = v;
				GO::retain(v);
			}
			return true;
		}
		return false;
	}
	bool insert(gint index, T* v) {
		if (index < 0) {
			return false;
		}
		gint dc = getCount();
		if (index > dc) {
			return false;
		}
		if (!changeCount(dc + 1)) {
			return false;
		}
		memmove((void*)&(GX_CAST_R(T**, m_Data.getPtr())[index + 1]),
			(void*)&(GX_CAST_R(T**, m_Data.getPtr())[index]),
			(size_t)(dc - index)*sizeof(T*));
		GX_CAST_R(T**, m_Data.getPtr())[index] = v;
		GO::retain(v);
		return true;
	}

	bool remove(gint index) {
		gint dc = getCount();
		if (index >= 0 && index<dc) {
			GO::release(GX_CAST_R(T**, m_Data.getPtr())[index]);
			memmove((void*)&(GX_CAST_R(T**, m_Data.getPtr())[index]),
				(void*)&(GX_CAST_R(T**, m_Data.getPtr())[index + 1]),
				(size_t)(dc - index - 1)*sizeof(T*));
			if (changeCount(dc - 1)) {
				return true;
			}
		}
		return false;
	}
    bool remove(T* v) {
        for(gint i=0;i<getCount();i++) {
            if(v==GX_CAST_R(T**, m_Data.getPtr())[i]) {
                return remove(i);
            }
        }
        return false;
    }

	bool remove(gint indexFrom, gint indexCount) {
		if (indexFrom<0 || indexCount <= 0) {
			return false;
		}
		gint dc = getCount();
		if (dc <= 0 || indexFrom + indexCount>dc) {
			return false;
		}
		for (gint i = indexFrom; i < indexFrom + indexCount; i++) {
			GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
		}
		memmove((void*)&(GX_CAST_R(T**, m_Data.getPtr())[indexFrom]),
			(void*)&(GX_CAST_R(T**, m_Data.getPtr())[indexFrom + indexCount]),
			(dc - indexFrom - indexCount)*sizeof(T*));
		return changeCount(dc - indexCount);
	}
    
    bool removeLast() {
        gint dc=getCount();
        if (dc<=0) {
            return true;
        }
        --dc;
        GO::release(GX_CAST_R(T**, m_Data.getPtr())[dc]);
        return changeCount(dc);
    }
    bool removeLast(gint count) {
        gint dc=getCount();
        if (dc<=0) {
            return true;
        }
        if (dc<count) {
            count=dc;
        }
        for (gint i=dc-count; i<dc; ++i) {
            GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
        }
        return changeCount(dc-count);
    }

	void removeAll() {
		for (gint i = 0; i < getCount(); i++) {
			GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
		}
		changeCount(0);
	}
    
    bool move(gint fromIdx,gint toIdx) {
        gint count=getCount();
        if (fromIdx<0 || fromIdx>=count) {
            return false;
        }
        if (toIdx<0) {
            toIdx=0;
        }
        else if(toIdx>=count) {
            toIdx=count-1;
        }
        if (fromIdx==toIdx) {
            return true;
        }
        
        T* obj=((T**)m_Data.getPtr())[fromIdx];
        if (fromIdx<toIdx) {
            memmove((void*)&(((T**)m_Data.getPtr())[fromIdx]),(const void*)&(((T**)m_Data.getPtr())[fromIdx+1]),(toIdx-fromIdx)*sizeof(T*));
        }
        else {
            memmove((void*)&(((T**)m_Data.getPtr())[toIdx+1]),(const void*)&(((T**)m_Data.getPtr())[toIdx]),(fromIdx-toIdx)*sizeof(T*));
        }
        ((T**)m_Data.getPtr())[toIdx]=obj;
        return true;
    }
    

protected:
	inline bool changeCount(gint toCount) {
		return m_Data.changeBytes(GX_CAST_S(guint, toCount)*sizeof(T*));
	}
private:
#if !defined(GX_OS_DESKTOP)
	GX::PieceData<sizeof(void*) * 8> m_Data;
#else
	GX::PieceData<sizeof(void*) * 16> m_Data;
#endif
	
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(class T, GArray<T>, GArrayBase);

template <class T>
GArray<T>::GArray()
{

}
template <class T>
GArray<T>::~GArray()
{
	for (gint i = 0; i < getCount(); i++) {
		GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
	}
}

#include "GXGObjectUD.h"

#endif
