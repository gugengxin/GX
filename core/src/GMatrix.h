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
	GMatrix4(const GMatrix4& copy);

	void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	void setIdentity();
    void setTranslation(float xTranslation, float yTranslation, float zTranslation);
    void setScale(float xScale, float yScale, float zScale);
    void setRotation(float axisX,float axisY,float axisZ, float radians);
    void setRotationX(float radians);
    void setRotationY(float radians);
    void setRotationZ(float radians);
	void setPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane);
	void setOrthographic(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
	void setLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
		float targetPositionX, float targetPositionY, float targetPositionZ,
		float upX, float upY, float upZ);

	void transpose();
	void translate(float tx, float ty, float tz);
	void scale(float sx, float sy, float sz);
	void rotate(float rx, float ry, float rz, float radians);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);

	void multiply(const GMatrix4& mat);

	inline const GMatrix4 operator*(const GMatrix4& mat) const
	{
		GMatrix4 result(*this);
		result.multiply(mat);
		return result;
	}
public:
	float m[16];
};

