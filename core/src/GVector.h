#ifndef GVector_h
#define GVector_h


#include "GXPrefix.h"


class GVector2
{
public:
	GVector2() : x(0.0f),y(0.0f) {}
    GVector2(float vx,float vy) : x(vx),y(vy) {}

    inline void set(float vx, float vy) {
        x = vx;
        y = vy;
    }

public:
	float x;
	float y;
};

class GVector3
{
public:
	static void subtract(const GVector3& v1, const GVector3& v2, GVector3& dst);
	static void cross(const GVector3& v1, const GVector3& v2, GVector3& dst);
	static float dot(const GVector3& v1, const GVector3& v2);
public:
	GVector3() : x(0.0f), y(0.0f), z(0.0f) {}
	GVector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	inline void set(float vx, float vy, float vz) {
		x = vx;
		y = vy;
		z = vz;
	}
	inline float* getPtr() {
		return &x;
	}

	float length();
	void normalize();
	void scale(float s) {
		x *= s;
		y *= s;
		z *= s;
	}

	void operator += (const GVector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	GVector3 operator * (float v) {
		return GVector3(x*v, y*v, z*v);
	}

public:
	float x;
	float y;
	float z;
};


class GVector4
{
public:
	GVector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

public:
	float x;
	float y;
	float z;
	float w;
};

#endif
