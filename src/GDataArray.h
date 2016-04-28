#pragma once

#include "GXPrefix.h"
#include "GPieceData.h"

class GDataArrayBase : public GObject {
	GX_OBJECT(GDataArrayBase);
};

template <typename T,guint N>
class GDataArray : public GDataArrayBase {
    GX_OBJECT(GDataArray);
public:
	inline gint getCount() {
		return (gint)(m_Data.getBytes() / sizeof(T));
	}
	inline T get(gint index) {
		return GX_CAST_R(T*,m_Data.getPtr())[index];
	}
	inline T* getPtr(gint index) {
		return &GX_CAST_R(T*, m_Data.getPtr())[index];
	}
	inline T& get(gint index) {
		return GX_CAST_R(T*, m_Data.getPtr())[index];
	}
	inline void set(gint index,const T& v) {
		GX_CAST_R(T*, m_Data.getPtr())[index] = v;
	}
	bool add(const T& v) {
		gint dc = getCount();
		if (changeCount(dc + 1)) {
			GX_CAST_R(T*, m_Data.getPtr())[dc] = v;
			return true;
		}
		return false;
	}
	bool insert(gint index,const T& v) {
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
		memmove((void*)&(GX_CAST_R(T*, m_Data.getPtr())[index + 1]),
			(void*)&(GX_CAST_R(T*, m_Data.getPtr())[index]),
			(size_t)(dc - index)*sizeof(T));
		GX_CAST_R(T*, m_Data.getPtr())[index] = v;
		return true;
	}
	bool remove(gint index) {
		gint dc = getCount();
		if (index >= 0 && index<dc) {
			memmove((void*)&(GX_CAST_R(T*, m_Data.getPtr())[index]),
				(void*)&(GX_CAST_R(T*, m_Data.getPtr())[index + 1]),
				(size_t)(dc - index - 1)*sizeof(T));
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

		memmove((void*)&(GX_CAST_R(T*, m_Data.getPtr())[indexFrom]), 
			(void*)&(GX_CAST_R(T*, m_Data.getPtr())[indexFrom + indexCount]),
			(dc - indexFrom - indexCount)*sizeof(T));
		return changeCount(dc - indexCount);
	}

	void removeAll() {
		changeCount(0);
	}

private:
	inline bool changeCount(gint toCount) {
		return m_Data.changeBytes(GX_CAST_S(guint,toCount)*sizeof(T));
	}
private:
    GPieceData m_Data;
};

GX_OBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA guint N, GDataArray<T GX_COMMA N>, GDataArrayBase);

template <typename T,guint N>
GDataArray<T,N>::GDataArray():
m_Data(sizeof(T)*N)
{

}
template <typename T,guint N>
GDataArray<T,N>::~GDataArray()
{
    
}


#if defined(GX_OS_MOBILE)
#define GX_DARRAY_N 8
#else
#define GX_DARRAY_N 16
#endif

template <typename T>
class GDArray : public GDataArray<T, GX_DARRAY_N> {
	GX_OBJECT(GDArray);
};

GX_OBJECT_TEMPLATE_IMPLEMENT(typename T, GDArray<T>, GDataArray<T GX_COMMA GX_DARRAY_N>);

template <typename T>
GDArray<T>::GDArray()
{

}
template <typename T>
GDArray<T>::~GDArray()
{

}