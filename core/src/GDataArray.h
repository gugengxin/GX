#ifndef GDataArray_h
#define GDataArray_h

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
    bool isEmpty() const {
        return m_Data.getBytes()<=0;
    }
	gint getCount() const {
		return (gint)(m_Data.getBytes() / sizeof(T));
	}
    guint getBytes() const {
        return m_Data.getBytes();
    }
    T& get(gint index) const {
        return GX_CAST_R(T*, m_Data.getPtr())[index];
    }
	T* getPtr(gint index) const {
		return &GX_CAST_R(T*, m_Data.getPtr())[index];
	}
	T& first() const {
		return GX_CAST_R(T*, m_Data.getPtr())[0];
	}
	T& last() const {
		return GX_CAST_R(T*, m_Data.getPtr())[(m_Data.getBytes() / sizeof(T))-1];
	}
    
    gint getIndex(const T& v) const {
        gint count=getCount();
        for (gint i=0; i<count; i++) {
            if (v==get(i)) {
                return i;
            }
        }
        return -1;
    }

	void set(gint index,const T& v) {
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
        move(index + 1, index, dc - index);
		GX_CAST_R(T*, m_Data.getPtr())[index] = v;
		return true;
	}
    bool insert(gint index,const T& v,gint count) {
        if (count<0) {
            return false;
        }
        if (index < 0) {
            return false;
        }
        gint dc = getCount();
        if (index > dc) {
            return false;
        }
        if (!changeCount(dc + count)) {
            return false;
        }
        move(index + count, index, dc - index);
        for (gint i=0; i<count; i++) {
            GX_CAST_R(T*, m_Data.getPtr())[index+i] = v;
        }
        return true;
    }
    
	bool remove(gint index) {
		gint dc = getCount();
		if (index >= 0 && index<dc) {
            move(index, index + 1, dc - index - 1);
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
        move(indexFrom, indexFrom + indexCount, dc - indexFrom - indexCount);
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
    
    inline bool push(const T& v) {
        return add(v);
    }
    
    T pop() {
        T res=last();
        removeLast();
        return res;
    }
    
protected:
	inline bool changeCount(gint toCount) {
		return m_Data.changeBytes(GX_CAST_S(guint,toCount)*GX_CAST_S(guint,sizeof(T)));
	}
    inline void move(gint idxTo, gint idx, gint len) {
        memmove((void*)&(GX_CAST_R(T*, m_Data.getPtr())[idxTo]),
                (void*)&(GX_CAST_R(T*, m_Data.getPtr())[idx]),
                len*sizeof(T));
    }
    bool expand(gint idx, gint len, gint lenTo) {
        gint cntCur=getCount();
        if (len > lenTo) {
            move(idx + lenTo, idx + len, cntCur - idx - len);
            return changeCount(cntCur - (len-lenTo)+1);
        }
        else if (len < lenTo) {
            if (!changeCount(cntCur + (lenTo-len)+1)) {
                return false;
            }
            move(idx + lenTo, idx + len, cntCur - idx - len);
        }
        return true;
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
class GPieceDataArray : public GDataArray<T, GX::PieceData<(guint32)(sizeof(T)*N)> > {
    friend class GString;
    GX_GOBJECT(GPieceDataArray);
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA guint32 N, GPieceDataArray<T GX_COMMA N>, GDataArray< T GX_COMMA GX::PieceData<(guint32)(sizeof(T)*N)> >);

template <typename T,guint32 N>
GPieceDataArray<T,N>::GPieceDataArray()
{
}
template <typename T,guint32 N>
GPieceDataArray<T,N>::~GPieceDataArray()
{
    
}


#if !defined(GX_OS_DESKTOP)
#define GX_PDARRAY_N 8
#else
#define GX_PDARRAY_N 16
#endif

template <typename T>
class GPDArray : public GPieceDataArray<T, GX_PDARRAY_N> {
	friend class GApplication;
    friend class GAutoreleasePool;
    friend class GThread;
	friend class GCanvas;
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

#endif
