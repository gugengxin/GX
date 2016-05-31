#include "GMatrix.h"
#include "GXMath.h"
#include "GVector.h"

const GMatrix4 GMatrix4::Identity = GMatrix4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);
const GMatrix4 GMatrix4::Zero = GMatrix4(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0);

GMatrix4::GMatrix4()
{
	m[0] = 1;     m[1] = 0;     m[2] = 0;     m[3] = 0;
	m[4] = 0;     m[5] = 1;     m[6] = 0;     m[7] = 0;
	m[8] = 0;     m[9] = 0;     m[10] = 1;    m[11] = 0;
	m[12] = 0;    m[13] = 0;    m[14] = 0;    m[15] = 1;
}

GMatrix4::GMatrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	m[0] = m11;
	m[1] = m21;
	m[2] = m31;
	m[3] = m41;
	m[4] = m12;
	m[5] = m22;
	m[6] = m32;
	m[7] = m42;
	m[8] = m13;
	m[9] = m23;
	m[10] = m33;
	m[11] = m43;
	m[12] = m14;
	m[13] = m24;
	m[14] = m34;
	m[15] = m44;
}

GMatrix4::GMatrix4(const GMatrix4& copy)
{
	memcpy(m, copy.m, GX_MATRIX_SIZE);
}

void GMatrix4::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	m[0] = m11;
	m[1] = m21;
	m[2] = m31;
	m[3] = m41;
	m[4] = m12;
	m[5] = m22;
	m[6] = m32;
	m[7] = m42;
	m[8] = m13;
	m[9] = m23;
	m[10] = m33;
	m[11] = m43;
	m[12] = m14;
	m[13] = m24;
	m[14] = m34;
	m[15] = m44;
}


void GMatrix4::setIdentity()
{
	memcpy(m, Identity.m, GX_MATRIX_SIZE);
}
void GMatrix4::setPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane)
{
	float f_n = 1.0f / (zFarPlane - zNearPlane);
	float theta = fieldOfView * 0.5f;
	float divisor = GX::tan(theta);
	float factor = 1.0f / divisor;

	memset(m, 0, GX_MATRIX_SIZE);

	m[0] = (1.0f / aspectRatio) * factor;
	m[5] = factor;
	m[10] = (-(zFarPlane + zNearPlane)) * f_n;
	m[11] = -1.0f;
	m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
}
void GMatrix4::setOrthographic(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
	memset(m, 0, GX_MATRIX_SIZE);
	m[0] = 2 / (right - left);
	m[5] = 2 / (top - bottom);
	m[10] = 2 / (zNearPlane - zFarPlane);

	m[12] = (left + right) / (left - right);
	m[13] = (top + bottom) / (bottom - top);
	m[14] = (zNearPlane + zFarPlane) / (zNearPlane - zFarPlane);
	m[15] = 1;
}
void GMatrix4::setLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
	float targetPositionX, float targetPositionY, float targetPositionZ,
	float upX, float upY, float upZ)
{
	GVector3 eye(eyePositionX, eyePositionY, eyePositionZ);
	GVector3 target(targetPositionX, targetPositionY, targetPositionZ);
	GVector3 up(upX, upY, upZ);
	up.normalize();

	GVector3 zaxis;
	GVector3::subtract(eye, target, zaxis);
	zaxis.normalize();

	GVector3 xaxis;
	GVector3::cross(up, zaxis, xaxis);
	xaxis.normalize();

	GVector3 yaxis;
	GVector3::cross(zaxis, xaxis, yaxis);
	yaxis.normalize();

	m[0] = xaxis.x;
	m[1] = yaxis.x;
	m[2] = zaxis.x;
	m[3] = 0.0f;

	m[4] = xaxis.y;
	m[5] = yaxis.y;
	m[6] = zaxis.y;
	m[7] = 0.0f;

	m[8] = xaxis.z;
	m[9] = yaxis.z;
	m[10] = zaxis.z;
	m[11] = 0.0f;

	m[12] = -GVector3::dot(xaxis, eye);
	m[13] = -GVector3::dot(yaxis, eye);
	m[14] = -GVector3::dot(zaxis, eye);
	m[15] = 1.0f;
}






