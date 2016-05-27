#pragma once

#include "GXPrefix.h"




class GMatrix4
{
public:
	static const GMatrix4 Zero;
	static const GMatrix4 Identity;
public:
	GMatrix4();
	GMatrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

public:
	float m[16];
};

