#ifndef GColor_h
#define GColor_h

#include "GXPrefix.h"

class GColor4
{
public:
	GColor4();
    GColor4(guint8 red, guint8 green, guint8 blue, guint8 alpha);

	inline void set(guint8 red, guint8 green, guint8 blue, guint8 alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	void set(float red, float green, float blue, float alpha);

	guint8 r, g, b, a;
};

class GColor4F
{
public:
	GColor4F();

	
	inline void set(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	void set(guint8 red, guint8 green, guint8 blue, guint8 alpha);

	float r, g, b, a;
};

#endif