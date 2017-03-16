#pragma once

#include "GXPrefix.h"
#include <string.h>
#include "GXData.h"
#include "GObject.h"

#include "GXGObject.h"

class GArrayBase : public GObject
{
	GX_GOBJECT(GArrayBase);
};

template <typename T>
class GArray : public GArrayBase {
	friend class GRunLoop;
	friend class GNCObserver;
	GX_GOBJECT(GArray);
public:
	inline gint getCount() {
		return (gint)(m_Data.getBytes() / sizeof(T*));
	}
	inline T* get(gint index) {
		return GX_CAST_R(T**, m_Data.getPtr())[index];
	}
    inline T* first() {
        if (m_Data.getBytes()>0) {
            return GX_CAST_R(T**, m_Data.getPtr())[0];
        }
        return NULL;
    }
    inline T* last() {
        if (m_Data.getBytes()>0) {
            return GX_CAST_R(T**, m_Data.getPtr())[(m_Data.getBytes() / sizeof(T*))-1];
        }
        return NULL;
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

	void removeAll() {
		for (gint i = 0; i < getCount(); i++) {
			GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
		}
		changeCount(0);
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

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GArray<T>, GArrayBase);

template <typename T>
GArray<T>::GArray()
{

}
template <typename T>
GArray<T>::~GArray()
{
	for (gint i = 0; i < getCount(); i++) {
		GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
	}
}

#include "GXGObjectUD.h"
