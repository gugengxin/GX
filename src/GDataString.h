//
//  GDataString.h
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GDataString_h
#define GDataString_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GOWHash.h"
#include "GData.h"
#include "GXEncoding.h"


namespace GX {
    template <typename T> gint strlen(const T* v)
    {
        gint res=0;
        while (*v) {
            res++;
            v++;
        }
        return res;
    }

	gint gi16toa(gint16 v, gchar* strOut, StringRadix radix);
	gint gu16toa(guint16 v, gchar* strOut, StringRadix radix);
	gint gi32toa(gint32 v, gchar* strOut, StringRadix radix);
	gint gu32toa(guint32 v, gchar* strOut, StringRadix radix);
	gint gi64toa(gint64 v, gchar* strOut, StringRadix radix);
	gint gu64toa(guint64 v, gchar* strOut, StringRadix radix);

	gint gi16toa(gint16 v, gwchar* strOut, StringRadix radix);
	gint gu16toa(guint16 v, gwchar* strOut, StringRadix radix);
	gint gi32toa(gint32 v, gwchar* strOut, StringRadix radix);
	gint gu32toa(guint32 v, gwchar* strOut, StringRadix radix);
	gint gi64toa(gint64 v, gwchar* strOut, StringRadix radix);
	gint gu64toa(guint64 v, gwchar* strOut, StringRadix radix);

	template <typename T> gint gf32toa(gfloat32 v, T* strOut, gint precision)
	{
		gfloat32 vTemp;
		gint32 decPos = 1;
		gfloat32 rv = 0.5f;
		for (gint i = 0; i < precision; i++) {
			rv *= 0.1f;
		}
		gint res = 0;

		if (v >= 0) {
			vTemp = v;
		}
		else {
			vTemp = -v;
			strOut[res++] = GX_CAST_S(T, '-');
		}
		vTemp += rv;
		while (vTemp>10.0f)
		{
			decPos++;
			vTemp /= 10.0f;
		}

		gint32 nTemp;

		if (precision <= 0) {
			for (gint i = 0; i < decPos; i++, res++) {
				nTemp = GX_CAST_S(gint32, vTemp);
				strOut[res] = GX_CAST_S(T, nTemp);
				vTemp -= nTemp;
				vTemp *= 10.0f;
			}
		}
		else {
			for (gint i = 0; i < decPos + precision + 1; i++, res++) {
				if (i == decPos) {
					strOut[res] = GX_CAST_S(T, '.');
				}
				else {
					nTemp = GX_CAST_S(gint32, vTemp);
					strOut[res] = GX_CAST_S(T, nTemp);
					vTemp -= nTemp;
					vTemp *= 10.0f;
				}
			}
		}
		return res;
	}

	template <typename T> gint gf64toa(gfloat64 v, T* strOut, gint precision)
	{
		gfloat64 vTemp;
		gint64 decPos = 1;
		gfloat64 rv = 0.5;
		for (gint i = 0; i < precision; i++) {
			rv *= 0.1f;
		}
		gint res = 0;

		if (v >= 0) {
			vTemp = v;
		}
		else {
			vTemp = -v;
			strOut[res++] = GX_CAST_S(T, '-');
		}
		vTemp += rv;
		while (vTemp>10.0)
		{
			decPos++;
			vTemp /= 10.0;
		}

		gint64 nTemp;
		if (precision <= 0) {
			for (gint i = 0; i < decPos; i++, res++) {
				nTemp = GX_CAST_S(gint64, vTemp);
				strOut[res] = GX_CAST_S(T, nTemp);
				vTemp -= nTemp;
				vTemp *= 10.0;
			}
		}
		else {
			for (gint i = 0; i < decPos + precision + 1; i++, res++) {
				if (i == decPos) {
					strOut[res] = GX_CAST_S(T, '.');
				}
				else {
					nTemp = GX_CAST_S(gint64, vTemp);
					strOut[res] = GX_CAST_S(T, nTemp);
					vTemp -= nTemp;
					vTemp *= 10.0;
				}
			}
		}
		return res;
	}

	void strUTF8toUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar* utf16Text, gint& ccUtf16Text);
	gint strUTF8toUTF16Count(const gchar* utf8Text, gint cbUtf8Text);
	gint strUTF8OneChartoUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar& utf16Out);
	void strUTF16toUTF8(const gwchar* utf16Text, gint ccUtf16Text, gchar* utf8Text, gint& cbUtf8Text);
	gint strUTF16toUTF8Count(const gwchar* utf16Text, gint ccUtf16Text);
	gint strUTF16OneChartoUTF8(const gwchar utf16Char, gchar* utf8Out);
}

template <typename T>
class GDataString : public GObject {
    GX_OBJECT(GDataString);
public:
    inline gint getLength() {
        return m_Length;
    }
    virtual guint getHash() {
        if (m_OWHash.codeA==0) {
            m_OWHash=GOWHash::compute(getDataPtr());
        }
        return m_OWHash.codeA;
    }
    virtual bool isEqual(GObject* obj) {
        if (obj->isKindOfClass(GDataString<T>::gclass)) {
            if (getHash()==obj->getHash()) {
                
                return m_OWHash.codeB==GX_CAST_R(GDataString<T>*, obj)->m_OWHash.codeB &&
                    m_OWHash.codeC==GX_CAST_R(GDataString<T>*, obj)->m_OWHash.codeC;
            }
        }
        return false;
    }
    
    void set(const T* v,gint len=-1,gint count=1)
    {
		if (count <= 0) {
			return;
		}
        if (len<0) {
            len=GX::strlen(v);
        }
		if (changeCapability(len*count+ 1)) {
			for (gint i = 0; i < count; i++) {
				memcpy(getDataPtr(i*len), v, len*sizeof(T));
			}
			setLength(len*count);
        }
    }
	void append(const T* v, gint len = -1, gint count = 1)
    {
		if (count <= 0) {
			return;
		}
        if (len<0) {
            len=GX::strlen(v);
        }
		gint lenCur = getLength();
		if (changeCapability(lenCur + len*count + 1)) {
			for (gint i = 0; i < count; i++) {
				memcpy(getDataPtr(lenCur+i*len), v, len*sizeof(T));
			}
			setLength(lenCur + len*count);
        }
    }
	void insert(gint idx, const T* v, gint len = -1, gint count = 1)
	{
		if (count <= 0) {
			return;
		}
		if (idx < 0) {
			return;
		}
		gint lenCur = getLength();
		if (idx > lenCur) {
			return;
		}
		if (len<0) {
			len = GX::strlen(v);
		}
		if (changeCapability(lenCur + len*count + 1)) {
			memmove(getDataPtr(idx) + len*count, getDataPtr(idx), (lenCur - idx)*sizeof(T));
			for (gint i = 0; i < count; i++) {
				memcpy(getDataPtr(idx + i*len), v, len*sizeof(T));
			}
			setLength(lenCur + len*count);
		}
	}
    
	void set(T v, gint count) {
		if (count <= 0) {
			return;
		}
		if (changeCapability(count + 1)) {
			for (gint i = 0; i < count; i++) {
				getDataPtr()[i] = v;
			}
			setLength(count);
		}
	}
	void append(T v, gint count) {
		if (count <= 0) {
			return;
		}
		gint lenCur = getLength();
		if (changeCapability(lenCur+count + 1)) {
			for (gint i = 0; i < count; i++) {
				getDataPtr(lenCur)[i] = v;
			}
			setLength(lenCur+count);
		}
	}
	void insert(gint idx, T v, gint count) {
		if (count <= 0) {
			return;
		}
		if (idx < 0) {
			return;
		}
		gint lenCur = getLength();
		if (idx > lenCur) {
			return;
		}
		if (changeCapability(lenCur + count + 1)) {
			memmove(getDataPtr(idx) + count, getDataPtr(idx), (lenCur - idx)*sizeof(T));
			for (gint i = 0; i < count; i++) {
				getDataPtr(idx)[i] = v;
			}
			setLength(lenCur + count);
		}
	}
	
	void clear() {
        if(changeCapability(0)) {
            setLength(0);
        }
    }
    
#define M_SET \
	if (vsLen < 0 && tempLen < -vsLen) {\
		set(fillChar, -vsLen - tempLen);\
		append(temp, tempLen);\
	}\
	else if (vsLen > 0 && tempLen < vsLen) {\
		set(temp, tempLen);\
		append(fillChar, vsLen - tempLen);\
	}\
	else {\
		set(temp, tempLen);\
	}
#define M_APPEND \
	if (vsLen < 0 && tempLen < -vsLen) {\
		append(fillChar, -vsLen - tempLen);\
		append(temp, tempLen);\
	}\
	else if (vsLen > 0 && tempLen < vsLen) {\
		append(temp, tempLen);\
		append(fillChar, vsLen - tempLen);\
	}\
	else {\
		append(temp, tempLen);\
	}
#define M_INSERT \
	if (vsLen < 0 && tempLen < -vsLen) {\
		insert(idx, fillChar, -vsLen - tempLen);\
		insert(idx - vsLen - tempLen, temp, tempLen);\
	}\
	else if (vsLen > 0 && tempLen < vsLen) {\
		insert(idx, temp, tempLen);\
		insert(idx + tempLen, fillChar, vsLen - tempLen);\
	}\
	else {\
		insert(idx, temp, tempLen);\
	}

	void setInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T,' ')) {
		T temp[16];
		gint tempLen = GX::gi16toa(v, temp, radix);
		M_SET
	}
	void appendInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[16];
		gint tempLen = GX::gi16toa(v, temp, radix);
		M_APPEND
	}
	void insertInt16(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[16];
		gint tempLen = GX::gi16toa(v, temp, radix);
		M_INSERT
	}
	void setUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[16];
		gint tempLen = GX::gu16toa(v, temp, radix);
		M_SET
	}
	void appendUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[16];
		gint tempLen = GX::gu16toa(v, temp, radix);
		M_APPEND
	}
	void insertUint16(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[16];
		gint tempLen = GX::gu16toa(v, temp, radix);
		M_INSERT
	}

	void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gi32toa(v, temp, radix);
		M_SET
	}
	void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gi32toa(v, temp, radix);
		M_APPEND
	}
	void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gi32toa(v, temp, radix);
		M_INSERT
	}
	void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gu32toa(v, temp, radix);
		M_SET
	}
	void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gu32toa(v, temp, radix);
		M_APPEND
	}
	void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[32];
		gint tempLen = GX::gu32toa(v, temp, radix);
		M_INSERT
	}

	void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gi64toa(v, temp, radix);
		M_SET
	}
	void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gi64toa(v, temp, radix);
		M_APPEND
	}
	void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gi64toa(v, temp, radix);
		M_INSERT
	}
	void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gu64toa(v, temp, radix);
		M_SET
	}
	void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gu64toa(v, temp, radix);
		M_APPEND
	}
	void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[64];
		gint tempLen = GX::gu64toa(v, temp, radix);
		M_INSERT
	}

	void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[8 + precision];
		gint tempLen = GX::gf32toa(v, temp, precision);
		M_SET
	}
	void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[8 + precision];
		gint tempLen = GX::gf32toa(v, temp, precision);
		M_APPEND
	}
	void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[8 + precision];
		gint tempLen = GX::gf32toa(v, temp, precision);
		M_INSERT
	}

	void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[17 + precision];
		gint tempLen = GX::gf64toa(v, temp, precision);
		M_SET
	}
	void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[17 + precision];
		gint tempLen = GX::gf64toa(v, temp, precision);
		M_APPEND
	}
	void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		T temp[17 + precision];
		gint tempLen = GX::gf64toa(v, temp, precision);
		M_INSERT
	}

#undef M_SET
#undef M_APPEND
#undef M_INSERT

	void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		setInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		setInt64(v, radix, vsLen, fillChar);
#endif
	}
	void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		appendInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		appendInt64(v, radix, vsLen, fillChar);
#endif
	}
	void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		insertInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		insertInt64(v, radix, vsLen, fillChar);
#endif
	}
	void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		setUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		setUint64(v, radix, vsLen, fillChar);
#endif
	}
	void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		appendUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		appendUint64(v, radix, vsLen, fillChar);
#endif
	}
	void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
#if GX_PTR_32BIT
		insertUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
		insertUint64(v, radix, vsLen, fillChar);
#endif
	}

	void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		setUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
	}
	void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		appendUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
	}
	void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, T fillChar = GX_CAST_S(T, ' ')) {
		insertUint(idx, GX_CAST_R(guint, v), radix, vsLen, fillChar);
	}

protected:
    inline T* getDataPtr() {
        return GX_CAST_R(T*, m_Data.getPtr());
    }
    inline T* getDataPtr(gint idx) {
        return &GX_CAST_R(T*, m_Data.getPtr())[idx];
    }
    bool changeCapability(gint count) {
        count=(count+32-1)/32;
        return m_Data.changeBytes(GX_CAST_S(guint, count)*sizeof(T));
    }
    void setLength(gint v) {
        if (getDataPtr()) {
            getDataPtr()[v]=0;
        }
        m_Length=v;
        m_OWHash.codeA=0;
    }
private:
    GData           m_Data;
    gint            m_Length;
    GOWHash::Code   m_OWHash;
};


GX_OBJECT_TEMPLATE_IMPLEMENT(typename T, GDataString<T>, GObject);

template <typename T>
GDataString<T>::GDataString()
{
    m_Length=0;
    m_OWHash.codeA=0;
    m_OWHash.codeB=0;
    m_OWHash.codeC=0;
}

template <typename T>
GDataString<T>::~GDataString()
{
    
}


#endif /* GDataString_h */
