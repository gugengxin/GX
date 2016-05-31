#include "GVector.h"
#include "GXMath.h"


void GVector3::subtract(const GVector3& v1, const GVector3& v2, GVector3& dst)
{
	dst.x = v1.x - v2.x;
	dst.y = v1.y - v2.y;
	dst.z = v1.z - v2.z;
}
void GVector3::cross(const GVector3& v1, const GVector3& v2, GVector3& dst)
{
	GX::vector3Cross(&v1.x, &v2.x, &dst.x);
}
float dot(const GVector3& v1, const GVector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float GVector3::length()
{
	return GX::sqrt(x*x + y*y + z*z);
}

void GVector3::normalize()
{
	float n = x * x + y * y + z * z;
	// Already normalized.
	if (n == 1.0f)
		return;

	n = GX::sqrt(n);

	n = 1.0f / n;
	x *= n;
	y *= n;
	z *= n;
}
