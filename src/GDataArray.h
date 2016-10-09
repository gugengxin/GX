#pragma once

#include "GXPrefix.h"
#include <string.h>
#include "GXData.h"
#include "GObject.h"

#include "GXGObject.h"

class GDataArrayBase : public GObject {
	GX_GOBJECT(GDataArrayBase);
};

template <typename T,typename DT>
class GDataArray : public GDataArrayBase {
    GX_GOBJECT(GDataArray);
public:
	inline gint getCount() {
		return (gint)(m_Data.getBytes() / sizeof(T));
	}
    inline guint getBytes() {
        return m_Data.getBytes();
    }
    inline T& get(gint index) {
        return GX_CAST_R(T*, m_Data.getPtr())[index];
    }
	inline T* getPtr(gint index) {
		return &GX_CAST_R(T*, m_Data.getPtr())[index];
	}
	inline T& first() {
		return GX_CAST_R(T*, m_Data.getPtr())[0];
	}
	inline T& last() {
		return GX_CAST_R(T*, m_Data.getPtr())[(m_Data.getBytes() / sizeof(T))-1];
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
    bool add(const T& v,gint count) {
        if (count<0) {
            return false;
        }
        else if(count==0) {
            return true;
        }
        gint dc = getCount();
        if (changeCount(dc + count)) {
            for(gint i=0;i<count;i++) {
                GX_CAST_R(T*, m_Data.getPtr())[dc+i] = v;
            }
            return true;
        }
        return false;
    }
    bool add(GDataArray* other) {
        gint oc = other->getCount();
        if(oc<0) {
            return false;
        }
        else if(oc==0) {
            return true;
        }
        gint dc = getCount();
        if (changeCount(dc + oc)) {
            memcpy((void*)&GX_CAST_R(T*, m_Data.getPtr())[dc], other->getPtr(0), other->getBytes());
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
    bool removeLast() {
        gint dc=getCount();
        if (dc<=0) {
            return true;
        }
        return changeCount(dc-1);
    }
    bool removeFrom(gint indexFrom) {
        if (indexFrom<0) {
            return false;
        }
        gint dc = getCount();
        if (indexFrom>=dc) {
            return false;
        }
        return changeCount(indexFrom);
    }
	void removeAll() {
		changeCount(0);
	}
    inline void zeroSelf() {
        m_Data.zeroSelf();
    }
protected:
	inline bool changeCount(gint toCount) {
		return m_Data.changeBytes(GX_CAST_S(guint,toCount)*GX_CAST_S(guint,sizeof(T)));
	}
    inline DT& getData() {
        return m_Data;
    }
private:
    DT m_Data;
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA typename DT, GDataArray<T GX_COMMA DT>, GDataArrayBase);

template <typename T,typename DT>
GDataArray<T,DT>::GDataArray()
{

}
template <typename T,typename DT>
GDataArray<T,DT>::~GDataArray()
{
    
}


template <typename T>
class GDArray : public GDataArray<T, GX::Data> {
	GX_GOBJECT(GDArray);
    template <typename,typename> friend class GMap;
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GDArray<T>, GDataArray<T GX_COMMA GX::Data>);

template <typename T>
GDArray<T>::GDArray()
{

}
template <typename T>
GDArray<T>::~GDArray()
{

}


template <typename T,guint32 N>
class GPieceDataArray : public GDataArray<T, GX::PieceData< (guint32)sizeof(T)*N >> {
    GX_GOBJECT(GPieceDataArray);
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA guint32 N, GPieceDataArray<T GX_COMMA N>, GDataArray<T GX_COMMA GX::PieceData< (guint32)sizeof(T)*N >>);

template <typename T,guint32 N>
GPieceDataArray<T,N>::GPieceDataArray()
{
}
template <typename T,guint32 N>
GPieceDataArray<T,N>::~GPieceDataArray()
{
    
}


#if defined(GX_OS_MOBILE)
#define GX_PDARRAY_N 8
#else
#define GX_PDARRAY_N 16
#endif

template <typename T>
class GPDArray : public GPieceDataArray<T, GX_PDARRAY_N> {
	friend class GApplication;
    friend class GAutoreleasePool;
    friend class GThread;
	friend class GPainter;
	friend class GOGLContext;
    GX_GOBJECT(GPDArray);
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GPDArray<T>, GPieceDataArray<T GX_COMMA GX_PDARRAY_N>);

template <typename T>
GPDArray<T>::GPDArray()
{
    
}
template <typename T>
GPDArray<T>::~GPDArray()
{
    
}

#include "GXGObjectUD.h"
