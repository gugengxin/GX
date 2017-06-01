#include "GColor.h"


GColor4::GColor4()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

GColor4::GColor4(guint8 red, guint8 green, guint8 blue, guint8 alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void GColor4::setFloat(float red, float green, float blue, float alpha)
{
	r = GX_CAST_S(guint8, red*255.0f);
	g = GX_CAST_S(guint8, green*255.0f);
	b = GX_CAST_S(guint8, blue*255.0f);
	a = GX_CAST_S(guint8, alpha*255.0f);
}


GColor4F::GColor4F()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

GColor4F::GColor4F(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void GColor4F::setUChar(guint8 red, guint8 green, guint8 blue, guint8 alpha)
{
	float s = 1.0f / 255.0f;
	r = red*s;
	g = green*s;
	b = blue*s;
	a = alpha*s;
}
