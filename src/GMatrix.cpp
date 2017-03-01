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
	m[1] = m12;
	m[2] = m13;
	m[3] = m14;
	m[4] = m21;
	m[5] = m22;
	m[6] = m23;
	m[7] = m24;
	m[8] = m31;
	m[9] = m32;
	m[10] = m33;
	m[11] = m34;
	m[12] = m41;
	m[13] = m42;
	m[14] = m43;
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
    m[1] = m12;
    m[2] = m13;
    m[3] = m14;
    m[4] = m21;
    m[5] = m22;
    m[6] = m23;
    m[7] = m24;
    m[8] = m31;
    m[9] = m32;
    m[10] = m33;
    m[11] = m34;
    m[12] = m41;
    m[13] = m42;
    m[14] = m43;
    m[15] = m44;
}


void GMatrix4::setIdentity()
{
	memcpy(m, Identity.m, GX_MATRIX_SIZE);
}
void GMatrix4::setTranslation(float xTranslation, float yTranslation, float zTranslation)
{
    memcpy(m, &Identity, GX_MATRIX_SIZE);
    
    m[12] = xTranslation;
    m[13] = yTranslation;
    m[14] = zTranslation;
}
void GMatrix4::setScale(float xScale, float yScale, float zScale)
{
    memcpy(m, &Identity, GX_MATRIX_SIZE);
    
    m[0] = xScale;
    m[5] = yScale;
    m[10] = zScale;
}
void GMatrix4::setRotation(float axisX,float axisY,float axisZ, float radians)
{
    float x = axisX;
    float y = axisY;
    float z = axisZ;
    
    // Make sure the input axis is normalized.
    float n = x*x + y*y + z*z;
    if (n != 1.0f)
    {
        // Not normalized.
        n = sqrtf(n);
        // Prevent divide too close to zero.
        if (n > 0.000001f)
        {
            n = 1.0f / n;
            x *= n;
            y *= n;
            z *= n;
        }
    }
    
    float c;
    float s;
    GX::sincos(radians, s, c);
    
    float t = 1.0f - c;
    float tx = t * x;
    float ty = t * y;
    float tz = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx = s * x;
    float sy = s * y;
    float sz = s * z;
    
    m[0] = c + tx*x;
    m[1] = txy + sz;
    m[2] = txz - sy;
    m[3] = 0.0f;
    
    m[4] = txy - sz;
    m[5] = c + ty*y;
    m[6] = tyz + sx;
    m[7] = 0.0f;
    
    m[8] = txz + sy;
    m[9] = tyz - sx;
    m[10] = c + tz*z;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}
void GMatrix4::setRotationX(float radians)
{
    memcpy(m, &Identity, GX_MATRIX_SIZE);
    
    float c;
    float s;
    GX::sincos(radians, s, c);
    
    m[5]  = c;
    m[6]  = s;
    m[9]  = -s;
    m[10] = c;
}
void GMatrix4::setRotationY(float radians)
{
    memcpy(m, &Identity, GX_MATRIX_SIZE);
    
    float c;
    float s;
    GX::sincos(radians, s, c);
    
    m[0]  = c;
    m[2]  = -s;
    m[8]  = s;
    m[10] = c;
}
void GMatrix4::setRotationZ(float radians)
{
    memcpy(m, &Identity, GX_MATRIX_SIZE);
    
    float c;
    float s;
    GX::sincos(radians, s, c);
    
    m[0] = c;
    m[1] = s;
    m[4] = -s;
    m[5] = c;
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

void GMatrix4::transpose()
{
    GX::matrixTranspose(m, m);
}
void GMatrix4::translate(float tx, float ty, float tz)
{
    GMatrix4 t;
    t.setTranslation(tx, ty, tz);
    GX::matrixMultiply(m, t.m, m);
}
void GMatrix4::scale(float sx, float sy, float sz)
{
    GMatrix4 s;
    s.setScale(sx, sy, sz);
    GX::matrixMultiply(m, s.m, m);
}
void GMatrix4::rotate(float rx, float ry, float rz, float radians)
{
    GMatrix4 r;
    r.setRotation(rx, ry, rz, radians);
    GX::matrixMultiply(m, r.m, m);
}
void GMatrix4::rotateX(float radians)
{
    GMatrix4 r;
    r.setRotationX(radians);
    GX::matrixMultiply(m, r.m, m);
}
void GMatrix4::rotateY(float radians)
{
    GMatrix4 r;
    r.setRotationY(radians);
    GX::matrixMultiply(m, r.m, m);
}
void GMatrix4::rotateZ(float radians)
{
    GMatrix4 r;
    r.setRotationZ(radians);
    GX::matrixMultiply(m, r.m, m);
}

void GMatrix4::multiply(const GMatrix4& mat)
{
    GX::matrixMultiply(m, mat.m, m);
}






