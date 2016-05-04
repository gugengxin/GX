//
//  GDataString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GDataString.h"


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