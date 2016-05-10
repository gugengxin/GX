#pragma once

#include "GXPrefix.h"
#include "GPieceData.h"
#include <string.h>

class GArrayBase : public GObject
{
	GX_OBJECT(GArrayBase);
};

template <typename T>
class GArray : public GArrayBase {
    friend class GApplication;
	friend class GRunLoop;
	GX_OBJECT(GArray);
public:
	inline gint getCount() {
		return (gint)(m_Data.getBytes() / sizeof(T*));
	}
	inline T* get(gint index) {
		return GX_CAST_R(T**, m_Data.getPtr())[index];
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
	GPieceData m_Data;
};

GX_OBJECT_TEMPLATE_IMPLEMENT(typename T, GArray<T>, GArrayBase);

template <typename T>
GArray<T>::GArray():
#if defined(GX_OS_MOBILE)
m_Data(sizeof(T*)*8)
#else
m_Data(sizeof(T*)*16)
#endif
{

}
template <typename T>
GArray<T>::~GArray()
{
	for (gint i = 0; i < getCount(); i++) {
		GO::release(GX_CAST_R(T**, m_Data.getPtr())[i]);
	}
}