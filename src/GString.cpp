//
//  GString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GString.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"


namespace GX
{
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

namespace GX
{
    static const gchar* g_NumChars = "0123456789abcdef0123456789ABCDEF";
    
    template <typename T> void _strSwap(T* str, gint len)
    {
        T temp;
        for (gint i = 0; i < len / 2; i++) {
            temp = str[i];
            str[i] = str[len - i-1];
            str[len - i - 1] = temp;
        }
    }
    
    gint gi16toa(gint16 v, gchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu16toa(GX_CAST_S(guint16, -v), strOut+1, radix) + 1;
        }
        return gu16toa(GX_CAST_S(guint16, v), strOut, radix);
    }
    gint gu16toa(guint16 v, gchar* strOut, StringRadix radix)
    {
        gint co = 0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint16 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co + vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    gint gi32toa(gint32 v, gchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu32toa(GX_CAST_S(guint32, -v), strOut+1, radix) + 1;
        }
        return gu32toa(GX_CAST_S(guint32, v), strOut, radix);
    }
    gint gu32toa(guint32 v, gchar* strOut, StringRadix radix)
    {
        gint co=0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint32 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co+vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    gint gi64toa(gint64 v, gchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu64toa(GX_CAST_S(guint64, -v), strOut+1, radix) + 1;
        }
        return gu64toa(GX_CAST_S(guint64, v), strOut, radix);
    }
    gint gu64toa(guint64 v, gchar* strOut, StringRadix radix)
    {
        gint co = 0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint64 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co + vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    
    gint gi16toa(gint16 v, gwchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu16toa(GX_CAST_S(guint16, -v), strOut+1, radix) + 1;
        }
        return gu16toa(GX_CAST_S(guint16, v), strOut, radix);
    }
    gint gu16toa(guint16 v, gwchar* strOut, StringRadix radix)
    {
        gint co = 0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint16 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co + vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    gint gi32toa(gint32 v, gwchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu32toa(GX_CAST_S(guint32, -v), strOut+1, radix) + 1;
        }
        return gu32toa(GX_CAST_S(guint32, v), strOut, radix);
    }
    gint gu32toa(guint32 v, gwchar* strOut, StringRadix radix)
    {
        gint co = 0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint32 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co + vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    gint gi64toa(gint64 v, gwchar* strOut, StringRadix radix)
    {
        if (radix == SR_Decimal && v<0) {
            strOut[0] = '-';
            return gu64toa(GX_CAST_S(guint64, -v), strOut+1, radix) + 1;
        }
        return gu64toa(GX_CAST_S(guint64, v), strOut, radix);
    }
    gint gu64toa(guint64 v, gwchar* strOut, StringRadix radix)
    {
        gint co = 0;
        if (radix == SR_HEX) {
            co = 16;
            radix = SR_Hex;
        }
        gint res = 0;
        guint64 vTemp;
        do {
            vTemp = v%radix;
            v /= radix;
            strOut[res] = g_NumChars[co + vTemp];
            res++;
        } while (v > 0);
        _strSwap(strOut, res);
        return res;
    }
    
    
    void strUTF8toUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar* utf16Text, gint& ccUtf16Text)
    {
        gint oldccUtf16Text = ccUtf16Text;
        while (cbUtf8Text > 0 && ccUtf16Text > 0)
        {
            if ((*utf8Text & 0x80) == 0)
            {
                *utf16Text = (gwchar)utf8Text[0];
                cbUtf8Text -= 1;
                utf8Text += 1;
            }
            else if ((*utf8Text & 0xE0) == 0xC0)
            {
                if (cbUtf8Text >= 2 && ((utf8Text[1] & 0xC0) == 0x80))
                {
                    *utf16Text = 0;
                    *utf16Text |= (utf8Text[0] & 0x1F) << 6;
                    *utf16Text |= (utf8Text[1] & 0x3F);
                    cbUtf8Text -= 2;
                    utf8Text += 2;
                }
                else
                {
                    break;
                }
            }
            else if ((*utf8Text & 0xF0) == 0xE0)
            {
                if (cbUtf8Text >= 3 && ((utf8Text[1] & 0xC0) == 0x80) && ((utf8Text[2] & 0xC0) == 0x80))
                {
                    *utf16Text = 0;
                    *utf16Text |= (utf8Text[0] & 0x1F) << 12;
                    *utf16Text |= (utf8Text[1] & 0x3F) << 6;
                    *utf16Text |= (utf8Text[2] & 0x3F);
                    cbUtf8Text -= 3;
                    utf8Text += 3;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            ccUtf16Text -= 1;
            utf16Text += 1;
        }
        ccUtf16Text = oldccUtf16Text - ccUtf16Text;
    }
    gint strUTF8toUTF16Count(const gchar* utf8Text, gint cbUtf8Text)
    {
        gint ccUtf16Text = 0;
        while (cbUtf8Text > 0)
        {
            if ((*utf8Text & 0x80) == 0)
            {
                cbUtf8Text -= 1;
                utf8Text += 1;
            }
            else if ((*utf8Text & 0xE0) == 0xC0)
            {
                if (cbUtf8Text >= 2 && ((utf8Text[1] & 0xC0) == 0x80))
                {
                    cbUtf8Text -= 2;
                    utf8Text += 2;
                }
                else
                {
                    break;
                }
            }
            else if ((*utf8Text & 0xF0) == 0xE0)
            {
                if (cbUtf8Text >= 3 && ((utf8Text[1] & 0xC0) == 0x80) && ((utf8Text[2] & 0xC0) == 0x80))
                {
                    cbUtf8Text -= 3;
                    utf8Text += 3;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            ++ccUtf16Text;
        }
        return ccUtf16Text;
    }
    gint strUTF8OneChartoUTF16(const gchar* utf8Text, gint cbUtf8Text, gwchar& utf16Out)
    {
        if ((*utf8Text & 0x80) == 0)
        {
            utf16Out = (gwchar)utf8Text[0];
            return 1;
        }
        else if ((*utf8Text & 0xE0) == 0xC0)
        {
            if (cbUtf8Text >= 2 && ((utf8Text[1] & 0xC0) == 0x80))
            {
                utf16Out = 0;
                utf16Out |= (utf8Text[0] & 0x1F) << 6;
                utf16Out |= (utf8Text[1] & 0x3F);
                return 2;
            }
        }
        else if ((*utf8Text & 0xF0) == 0xE0)
        {
            if (cbUtf8Text >= 3 && ((utf8Text[1] & 0xC0) == 0x80) && ((utf8Text[2] & 0xC0) == 0x80))
            {
                utf16Out = 0;
                utf16Out |= (utf8Text[0] & 0x1F) << 12;
                utf16Out |= (utf8Text[1] & 0x3F) << 6;
                utf16Out |= (utf8Text[2] & 0x3F);
                return 3;
            }
        }
        return 0;
    }
    void strUTF16toUTF8(const gwchar* utf16Text, gint ccUtf16Text, gchar* utf8Text, gint& cbUtf8Text)
    {
        gint oldcbUtf8Text = cbUtf8Text;
        while (ccUtf16Text > 0)
        {
            if ((*utf16Text & ~0x007F) == 0)
            {
                if (cbUtf8Text >= 1)
                {
                    utf8Text[0] = GX_CAST_S(gchar, *utf16Text);
                    cbUtf8Text -= 1;
                    utf8Text += 1;
                }
                else
                {
                    break;
                }
            }
            else if ((*utf16Text & ~0x07FF) == 0)
            {
                if (cbUtf8Text >= 2)
                {
                    utf8Text[0] = GX_CAST_S(gchar, 0xC0 | ((*utf16Text & 0x07C0) >> 6));
                    utf8Text[1] = GX_CAST_S(gchar, 0x80 | (*utf16Text & 0x003F));
                    
                    cbUtf8Text -= 2;
                    utf8Text += 2;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (cbUtf8Text >= 3)
                {
                    utf8Text[0] = GX_CAST_S(gchar, 0xE0 | ((*utf16Text & 0xF000) >> 12));
                    utf8Text[1] = GX_CAST_S(gchar, 0x80 | ((*utf16Text & 0x0FC0) >> 6));
                    utf8Text[2] = GX_CAST_S(gchar, 0x80 | (*utf16Text & 0x003F));
                    
                    cbUtf8Text -= 3;
                    utf8Text += 3;
                }
                else
                {
                    break;
                }
            }
            ccUtf16Text -= 1;
            utf16Text += 1;
        }
        cbUtf8Text = oldcbUtf8Text - cbUtf8Text;
    }
    gint strUTF16toUTF8Count(const gwchar* utf16Text, gint ccUtf16Text)
    {
        gint cbUtf8Text = 0;
        while (ccUtf16Text > 0)
        {
            if ((*utf16Text & ~0x007F) == 0)
            {
                cbUtf8Text += 1;
            }
            else if ((*utf16Text & ~0x07FF) == 0)
            {
                cbUtf8Text += 2;
            }
            else
            {
                cbUtf8Text += 3;
            }
            ccUtf16Text -= 1;
            utf16Text += 1;
        }
        return cbUtf8Text;
    }
    gint strUTF16OneChartoUTF8(const gwchar utf16Char, gchar* utf8Out)
    {
        if ((utf16Char & ~0x007F) == 0)
        {
            utf8Out[0] = GX_CAST_S(gchar,utf16Char);
            return 1;
        }
        else if ((utf16Char & ~0x07FF) == 0)
        {
            utf8Out[0] = GX_CAST_S(gchar, 0xC0 | ((utf16Char & 0x07C0) >> 6));
            utf8Out[1] = GX_CAST_S(gchar, 0x80 | (utf16Char & 0x003F));
            return 2;
        }
        else
        {
            utf8Out[0] = GX_CAST_S(gchar, 0xE0 | ((utf16Char & 0xF000) >> 12));
            utf8Out[1] = GX_CAST_S(gchar, 0x80 | ((utf16Char & 0x0FC0) >> 6));
            utf8Out[2] = GX_CAST_S(gchar, 0x80 | (utf16Char & 0x003F));
            return 3;
        }
        return 0;
    }
}




GString::Formater::Formater(GString* str, gint cursor, gint cursorEnd)
{
    m_String = str;
    m_Cursor = cursor;
    m_CursorEnd = cursorEnd;
}

bool GString::Formater::moveCursor()
{
    gint curEnd = m_String->getLength() - m_CursorEnd;
    while (m_Cursor<curEnd-1) {
        if (m_String->at(m_Cursor)==(guchar)'%' && m_String->at(m_Cursor + 1) == (guchar)'@') {
            return true;
        }
        else if (m_String->at(m_Cursor)==(guchar)'%' && m_String->at(m_Cursor + 1) == (guchar)'%') {
            m_String->remove(m_Cursor + 1, 1);
            m_Cursor++;
        }
        else {
            m_Cursor++;
        }
    }
    return false;
}
gint GString::Formater::replaceStart()
{
    return m_String->getLength();
}
void GString::Formater::replaceEnd(gint lastLen)
{
    m_Cursor=m_Cursor+2+(m_String->getLength()-lastLen);
}

GString::Formater& GString::Formater::arg(gchar v, gint count)
{
    if (moveCursor()) {
        gint lastLen=replaceStart();
        getString()->replace(getCursor(), 2, v, count);
        replaceEnd(lastLen);
    }
    return *this;
}

GString::Formater& GString::Formater::arg(gwchar v,gint count)
{
    if (moveCursor()) {
        gint lastLen=replaceStart();
        getString()->replace(getCursor(), 2, v, count);
        replaceEnd(lastLen);
    }
    return *this;
}




GX_GOBJECT_IMPLEMENT(GString, GObject);

GString::GString()
{
    m_OWHash.codeA=0;
    m_OWHash.codeB=0;
    m_OWHash.codeC=0;
}

GString::~GString()
{
    
}

bool GString::isEqual(GObject* obj)
{
    if (obj->isKindOfClass(GString::gclass)) {
        if (getHash() == obj->getHash()) {
            return getOWHashB() == GX_CAST_R(GString*, obj)->getOWHashB() &&
            getOWHashC() == GX_CAST_R(GString*, obj)->getOWHashC();
        }
    }
    return false;
}

gint GString::getLength()
{
    gint res=m_Buffer.getCount();
    if (res<=0) {
        return 0;
    }
    return res-1;
}

guint GString::getHash()
{
    if (m_OWHash.codeA==0) {
        m_OWHash=GOWHash::compute(m_Buffer.getPtr(0));
    }
    return m_OWHash.codeA;
}

guchar GString::at(gint idx)
{
    return m_Buffer.get(idx);
}

void GString::remove(gint idx, gint len)
{
    m_Buffer.remove(idx, len);
    modifyDone();
}

void GString::clear()
{
    m_Buffer.removeAll();
    modifyDone();
}

guchar* GString::prepareBuffer(gint len)
{
    m_Buffer.changeCount(len+1);
    setCStringEnd();
    modifyDone();
    return (guchar*)m_Buffer.getPtr(0);
}

void GString::cutOff(gint len)
{
    m_Buffer.changeCount(len+1);
    setCStringEnd();
    modifyDone();
}



void GString::set(gchar v, gint count)
{
    if (count <= 0) {
        return;
    }
    if(m_Buffer.changeCount(count+1)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::append(gchar v, gint count)
{
    if (count <= 0) {
        return;
    }
    gint lenCur = getLength();
    if (m_Buffer.changeCount(lenCur + count + 1)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(lenCur+i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::insert(gint idx, gchar v, gint count)
{
    replace(idx, 0, v, count);
}
void GString::replace(gint idx, gint lenR, gchar v, gint count)
{
    if (idx < 0 || lenR<0) {
        return;
    }
    if (count <= 0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (m_Buffer.expand(idx, lenR, count)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(idx+i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}

void GString::set(gwchar v, gint count)
{
    if (count <= 0) {
        return;
    }
    if(m_Buffer.changeCount(count+1)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::append(gwchar v, gint count)
{
    if (count <= 0) {
        return;
    }
    gint lenCur = getLength();
    if (m_Buffer.changeCount(lenCur + count + 1)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(lenCur+i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::insert(gint idx, gwchar v, gint count)
{
    replace(idx, 0, v, count);
}
void GString::replace(gint idx, gint lenR, gwchar v, gint count)
{
    if (idx < 0 || lenR<0) {
        return;
    }
    if (count <= 0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (m_Buffer.expand(idx, lenR, count)) {
        for (gint i=0; i<count; i++) {
            m_Buffer.set(idx+i, GX_CAST_S(guchar, v));
        }
        setCStringEnd();
        modifyDone();
    }
}

void GString::set(const gchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.changeCount(len*count + 1)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::append(const gchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    gint lenCur = getLength();
    if (m_Buffer.changeCount(lenCur + len*count + 1)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(lenCur+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::insert(gint idx, const gchar* v, gint len, gint count)
{
    replace(idx,0, v, len, count);
}
void GString::replace(gint idx, gint lenR, const gchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (idx < 0 || lenR<0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.expand(idx, lenR, len*count)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(idx+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::replace(gint idx, gint lenR,
                      gchar preChar, gint preCount,
                      gchar sufChar, gint sufCount,
                      const gchar* v, gint len, gint count)
{
    if (preCount <0 || count < 0 || sufCount<0 || preCount+count+sufCount<=0) {
        return;
    }
    if (idx < 0 || lenR<0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.expand(idx, lenR, preCount + len*count + sufCount)) {
        gint start = idx;
        for (gint i=0; i<preCount; i++) {
            m_Buffer.set(start+i, GX_CAST_S(guchar, preChar));
        }
        start += preCount;
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(start+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        start += len*count;
        for (gint i=0; i<sufCount; i++) {
            m_Buffer.set(start+i, GX_CAST_S(guchar, sufChar));
        }
        start += sufCount;
        
        setCStringEnd();
        modifyDone();
    }
}

void GString::set(const gwchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.changeCount(len*count + 1)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::append(const gwchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    gint lenCur = getLength();
    if (m_Buffer.changeCount(lenCur + len*count + 1)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(lenCur+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::insert(gint idx, const gwchar* v, gint len, gint count)
{
    replace(idx,0, v, len, count);
}
void GString::replace(gint idx, gint lenR, const gwchar* v, gint len, gint count)
{
    if (count <= 0) {
        return;
    }
    if (idx < 0 || lenR<0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.expand(idx, lenR, len*count)) {
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(idx+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        setCStringEnd();
        modifyDone();
    }
}
void GString::replace(gint idx, gint lenR,
                      gwchar preChar, gint preCount,
                      gwchar sufChar, gint sufCount,
                      const gwchar* v, gint len, gint count)
{
    if (preCount <0 || count < 0 || sufCount<0 || preCount+count+sufCount<=0) {
        return;
    }
    if (idx < 0 || lenR<0) {
        return;
    }
    gint lenCur = getLength();
    if (idx > lenCur) {
        return;
    }
    if (len<0) {
        len = GX::strlen(v);
    }
    if (m_Buffer.expand(idx, lenR, preCount + len*count + sufCount)) {
        gint start = idx;
        for (gint i=0; i<preCount; i++) {
            m_Buffer.set(start+i, GX_CAST_S(guchar, preChar));
        }
        start += preCount;
        for (gint j=0; j<count; j++) {
            for (gint i = 0; i < len; i++) {
                m_Buffer.set(start+j*len+i, GX_CAST_S(guchar, v[i]));
            }
        }
        start += len*count;
        for (gint i=0; i<sufCount; i++) {
            m_Buffer.set(start+i, GX_CAST_S(guchar, sufChar));
        }
        start += sufCount;
        
        setCStringEnd();
        modifyDone();
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
#define M_REPLACE \
replace(idx, lenR, \
fillChar, (vsLen < 0 && tempLen < -vsLen) ? -vsLen - tempLen : 0, \
fillChar, (vsLen > 0 && tempLen < vsLen) ? vsLen - tempLen : 0, \
temp, tempLen, 1);


void GString::setInt16(gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gi16toa(v, temp, radix);
    M_SET
}
void GString::appendInt16(gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gi16toa(v, temp, radix);
    M_APPEND
}
void GString::insertInt16(gint idx, gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceInt16(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gi16toa(v, temp, radix);
    M_REPLACE
}
void GString::setUint16(guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gu16toa(v, temp, radix);
    M_SET
}
void GString::appendUint16(guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gu16toa(v, temp, radix);
    M_APPEND
}
void GString::insertUint16(gint idx, guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceUint16(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[16];
    gint tempLen = GX::gu16toa(v, temp, radix);
    M_REPLACE
}

void GString::setInt32(gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gi32toa(v, temp, radix);
    M_SET
}
void GString::appendInt32(gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gi32toa(v, temp, radix);
    M_APPEND
}
void GString::insertInt32(gint idx, gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceInt32(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gi32toa(v, temp, radix);
    M_REPLACE
}
void GString::setUint32(guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gu32toa(v, temp, radix);
    M_SET
}
void GString::appendUint32(guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gu32toa(v, temp, radix);
    M_APPEND
}
void GString::insertUint32(gint idx, guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceUint32(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[32];
    gint tempLen = GX::gu32toa(v, temp, radix);
    M_REPLACE
}

void GString::setInt64(gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gi64toa(v, temp, radix);
    M_SET
}
void GString::appendInt64(gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gi64toa(v, temp, radix);
    M_APPEND
}
void GString::insertInt64(gint idx, gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceInt64(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gi64toa(v, temp, radix);
    M_REPLACE
}
void GString::setUint64(guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gu64toa(v, temp, radix);
    M_SET
}
void GString::appendUint64(guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gu64toa(v, temp, radix);
    M_APPEND
}
void GString::insertUint64(gint idx, guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceUint64(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    gchar temp[64];
    gint tempLen = GX::gu64toa(v, temp, radix);
    M_REPLACE
}

void GString::setFloat32(gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
    gchar temp[8 + 32];
    gint tempLen = GX::gf32toa(v, temp, precision);
    M_SET
}
void GString::appendFloat32(gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
    gchar temp[8 + 32];
    gint tempLen = GX::gf32toa(v, temp, precision);
    M_APPEND
}
void GString::insertFloat32(gint idx, gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
    replaceFloat32(idx, 0, v, precision, vsLen, fillChar);
}
void GString::replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
    if (precision > 30) {
        precision = 30;
    }
    gchar temp[8 + 32];
    gint tempLen = GX::gf32toa(v, temp, precision);
    M_REPLACE
}

void GString::setFloat64(gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
    if (precision > 30) {
        precision = 30;
    }
    gchar temp[17 + 32];
    gint tempLen = GX::gf64toa(v, temp, precision);
    M_SET
}
void GString::appendFloat64(gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
    if (precision > 30) {
        precision = 30;
    }
    gchar temp[17 + 32];
    gint tempLen = GX::gf64toa(v, temp, precision);
    M_APPEND
}
void GString::insertFloat64(gint idx, gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
    replaceFloat64(idx, 0, v, precision, vsLen, fillChar);
}
void GString::replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
    if (precision > 30) {
        precision = 30;
    }
    gchar temp[17 + 32];
    gint tempLen = GX::gf64toa(v, temp, precision);
    M_REPLACE
}

#undef M_SET
#undef M_APPEND
#undef M_REPLACE

void GString::setInt(gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    setInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    setInt64(v, radix, vsLen, fillChar);
#endif
}
void GString::appendInt(gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    appendInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    appendInt64(v, radix, vsLen, fillChar);
#endif
}
void GString::insertInt(gint idx, gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    insertInt32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    insertInt64(idx, v, radix, vsLen, fillChar);
#endif
}
void GString::replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    replaceInt32(idx, lenR, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    replaceInt64(idx, lenR, v, radix, vsLen, fillChar);
#endif
}

void GString::setUint(guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    setUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    setUint64(v, radix, vsLen, fillChar);
#endif
}
void GString::appendUint(guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    appendUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    appendUint64(v, radix, vsLen, fillChar);
#endif
}
void GString::insertUint(gint idx, guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    insertUint32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    insertUint64(idx, v, radix, vsLen, fillChar);
#endif
}
void GString::replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    replaceUint32(idx, v, lenR, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
    replaceUint64(idx, v, lenR, radix, vsLen, fillChar);
#endif
}

void GString::setFloat(gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    setFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
    setFloat64(v, precision, vsLen, fillChar);
#endif
}
void GString::appendFloat(gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    appendFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
    appendFloat64(v, precision, vsLen, fillChar);
#endif
}
void GString::insertFloat(gint idx, gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    insertFloat32(idx, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
    insertFloat64(idx, v, precision, vsLen, fillChar);
#endif
}
void GString::replaceFloat(gint idx, gint lenR, gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
    replaceFloat32(idx, lenR, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
    replaceFloat64(idx, lenR, v, precision, vsLen, fillChar);
#endif
}


void GString::setPtr(void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    setUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::appendPtr(void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    appendUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::insertPtr(gint idx, void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    insertUint(idx, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
    replaceUint(idx, lenR, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}

GString::Formater GString::format(const gchar* fmt, gint len)
{
    set(fmt, len);
    return Formater(this, 0, 0);
}

GString::Formater GString::appendFormat(const gchar* fmt, gint len)
{
    gint lenCur = getLength();
    append(fmt,len);
    return Formater(this, lenCur, 0);
}
GString::Formater GString::insertFormat(gint idx, const gchar* fmt, gint len)
{
    gint lenTemp = getLength() - idx;
    insert(idx, fmt, len);
    return Formater(this, idx, lenTemp);
}
GString::Formater GString::replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len)
{
    gint lenTemp = getLength() - idx - lenR;
    replace(idx, lenR, fmt, len);
    return Formater(this, idx, lenTemp);
}





bool GString::lastIsSeparator()
{
    gint count=m_Buffer.getCount();
    if (count>0) {
        const guchar c = m_Buffer.last();
        return (c == (guchar)'/' || c == (guchar)'\\');
    }
    return false;
}

void GString::appendPathComponent(const gchar* component, gint len)
{
    if (lastIsSeparator()) {
        if (component[0] == '/' || component[0] == '\\') {
            if (len < 0) {
                len = GX::strlen(component);
            }
            append(component + 1, len - 1);
        }
        else {
            append(component, len);
        }
    }
    else {
        if (component[0] == '/' || component[0] == '\\') {
            append(component, len);
        }
        else {
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
            append('\\');
#else
            append('/');
#endif
            append(component, len);
        }
    }
}

void GString::appendPathComponent(const gwchar* component, gint len)
{
    if (lastIsSeparator()) {
        if (component[0] == L'/' || component[0] == L'\\') {
            if (len < 0) {
                len = GX::strlen(component);
            }
            append(component + 1, len - 1);
        }
        else {
            append(component, len);
        }
    }
    else {
        if (component[0] == L'/' || component[0] == L'\\') {
            append(component, len);
        }
        else {
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
            append(L'\\');
#else
            append(L'/');
#endif
            append(component, len);
        }
    }
}






void GString::setCStringEnd()
{
    gint count=m_Buffer.getCount();
    if (count>0) {
        m_Buffer.set(count-1, 0);
    }
}

void GString::modifyDone()
{
    m_OWHash.codeA=0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const GX::UUID g_UUID(0x3932637B, 0x36333461, 0x32652D33, 0x342D6134);

const GX::UUID& GString::seGetUUID()
{
    return g_UUID;
}
gint GString::seGetBytes()
{
    gint res = seBytesOfKeyAndData(SKBuf, (guint)(getLength()*sizeof(guchar)));
    return res;
}
gint GString::seEncodeFields(GEncoder& coder)
{
    gint res = seEncodeKeyAndData(coder, SKBuf, m_Buffer.getPtr(0), (guint)(getLength()*sizeof(guchar)));
    return res;
}


const GX::UUID& GString::ueGetUUID()
{
    return g_UUID;
}

gint GString::ueDecodeField(GDecoder& coder, guint32 key, guint32 len)
{
    switch (key)
    {
        case SKBuf:
        {
            gint count = (gint)len/sizeof(guchar);
            if (m_Buffer.changeCount(count+1)) {
                gint res=ueDecodeData(coder, (void*)m_Buffer.getPtr(0), (guint)len);
                if (res < 0) {
                    return -1;
                }
                setCStringEnd();
                modifyDone();
                return res;
            }
            return -1;
        }
            break;
        default:
            return 0;
    }
}

