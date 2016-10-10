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
#include "GXData.h"
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

	template <typename T> gint gatoi(const T* buf, gint len=-1)
	{
		if (len < 0) {
			len = GX::strlen(buf);
		}
		gint res = 0;
		gint m = 1;
		gint i = 0;
		if (buf[i] == '-') {
			m = -1;
			i++;
		}
		for (; i < len; i++) {
			res = res*10+(buf[i]-'0');
		}
		return res*m;
	}
	template <typename T> gfloat gatof(const T* buf, gint len)
	{
		if (len < 0) {
			len = GX::strlen(buf);
		}
		gfloat res = 0.0f;
		gfloat frac = 0.0f;
		gfloat m = 1.0f;
		gint i = 0;
		if (buf[i] == '-') {
			m = -1.0f;
			i++;
		}
		for (; i < len; i++) {
			if (frac <= 0.0f) {
				if (buf[i] != '.') {
					res = res * 10.0f + (buf[i] - '0');
				}
				else {
					frac = 10.0f;
				}
			}
			else {
				res += (buf[i] - '0')/frac;
				frac *= 10.0f;
			}
		}
		return res*m;
	}


	void strUTF8toUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar* utf16Text, gint& ccUtf16Text);
	gint strUTF8toUTF16Count(const gchar* utf8Text, gint cbUtf8Text);
	gint strUTF8OneChartoUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar& utf16Out);
	void strUTF16toUTF8(const gwchar* utf16Text, gint ccUtf16Text, gchar* utf8Text, gint& cbUtf8Text);
	gint strUTF16toUTF8Count(const gwchar* utf16Text, gint ccUtf16Text);
	gint strUTF16OneChartoUTF8(const gwchar utf16Char, gchar* utf8Out);
}

#include "GXGObject.h"

template <typename T>
class GDataString : public GObject {
	friend class GString;
	friend class GWString;
    GX_GOBJECT(GDataString);
protected:
	class Formater {
	protected:
		Formater(GDataString* str, gint cursor, gint cursorEnd) {
			m_String = str;
			m_Cursor = cursor;
			m_CursorEnd = cursorEnd;
		}
        inline GDataString* getString() {
            return m_String;
        }
        inline gint getCursor() {
            return m_Cursor;
        }
        bool moveCursor() {
			gint curEnd = m_String->getLength() - m_CursorEnd;
			while (m_Cursor<curEnd-1) {
                if (m_String->at(m_Cursor)==(T)'%' &&
					m_String->at(m_Cursor + 1) == (T)'@') {
					return true;
                }
                else {
					m_Cursor ++;
                }
            }
            return false;
        }
        gint replaceStart() {
            return m_String->getLength();
        }
        void replaceEnd(gint lastLen) {
            m_Cursor=m_Cursor+2+(m_String->getLength()-lastLen);
        }
	private:
		GDataString* m_String;
		gint m_Cursor;
		gint m_CursorEnd;
	};
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
    T at(gint idx) {
        return *getDataPtr(idx);
    }
	void remove(gint idx, gint len) {
		if (len <= 0) {
			return;
		}
		if (idx < 0) {
			len += -idx;
			idx = 0;
		}
		else if (idx >= m_Length) {
			return;
		}
		if (idx + len>m_Length) {
			len = m_Length - idx;
		}
		move(idx, idx + len, (guint)(m_Length - idx - len));
		if (changeCapability(m_Length - len + 1)) {
			setLength(m_Length - len);
		}
	}
	void clear() {
        if(changeCapability(0)) {
            setLength(0);
        }
    }
	
	T* prepareBuffer(gint len) {
		changeCapability(len + 1);
		setLength(len);
		return getDataPtr();
	}
	void cutOff(gint len) {
		changeCapability(len + 1);
		setLength(len);
	}
public:
	bool lastIsSeparator() {
		if (m_Length > 0) {
			gtchar c = at(m_Length - 1);
			return (c == (gtchar)'/' || c == (gtchar)'\\');
		}
		return false;
	}

protected:
    inline T* getDataPtr() {
        return GX_CAST_R(T*, m_Data.getPtr());
    }
    inline T* getDataPtr(gint idx) {
        return &GX_CAST_R(T*, m_Data.getPtr())[idx];
    }
	inline void move(gint idxTo, gint idx, gint len) {
		memmove(getDataPtr(idxTo), getDataPtr(idx), sizeof(T)*len);
	}
	bool changeSize(gint idx, gint len, gint lenTo)
	{
		if (len > lenTo) {
			move(idx + lenTo, idx + len, m_Length - idx - len);
			return changeCapability(m_Length - (len-lenTo)+1);
		}
		else if (len < lenTo) {
			if (!changeCapability(m_Length + (lenTo-len)+1)) {
				return false;
			}
			move(idx + lenTo, idx + len, m_Length - idx - len);
		}
		return true;
	}
    bool changeCapability(gint count) {
		const gint STEP = 32;
		gint nTemp = (m_Length + STEP - 1) / STEP * STEP;
		if (count>nTemp || count <nTemp - STEP*2) {
			nTemp = (count + STEP - 1) / STEP * STEP;
			return m_Data.changeBytes(GX_CAST_S(guint, nTemp)*sizeof(T));
		}
		return true;
    }
    void setLength(gint v) {
        if (getDataPtr()) {
            getDataPtr()[v]=0;
        }
        m_Length=v;
        m_OWHash.codeA=0;
    }
	inline guint32 getOWHashA() {
		return m_OWHash.codeA;
	}
	inline guint32 getOWHashB() {
		return m_OWHash.codeB;
	}
	inline guint32 getOWHashC() {
		return m_OWHash.codeC;
	}
private:
    GX::Data		m_Data;
    gint            m_Length;
    GOWHash::Code   m_OWHash;
};


GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GDataString<T>, GObject);

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

#include "GXGObjectUD.h"

#endif /* GDataString_h */
