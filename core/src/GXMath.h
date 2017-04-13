#pragma once
#include "GXPrefix.h"
#include <math.h>
#include <float.h>


#define GX_MATRIX_SIZE (sizeof(float) * 16)
#define GX_PI        3.14159265358979f
#define GX_PI_2      1.57079632679490f
#define GX_PI_4      0.78539816339745f
#define GX_PI_8      0.39269908169872f

namespace GX
{
	/// 交换两个变量的值
	template<typename T> void swap(T &a, T &b)
	{
#if defined(GX_ASM)
		__asm
		{
			mov eax, dword ptr[a];
			mov ebx, dword ptr[b];
			fld dword ptr[eax]
			fld dword ptr[ebx]
			fstp dword ptr[eax]
			fstp dword ptr[ebx]
		}
#else
		T c = b;
		b = a;
		a = c;
#endif
	}
	/// 角度转弧度
	inline float degreeToRadian(float r) {
		return r * GX_PI/180.0f;
	}
	/// 角度转弧度
	inline float degToRad(float r) {
		return degreeToRadian(r);
	}
	/// 弧度转角度
	inline float radianToDegree(float r) {
		return r * 180.0f / GX_PI;
	}
	/// 弧度转角度
	inline float radToDeg(float r)
	{
		return radianToDegree(r);
	}
	/// 绝对值
	inline float abs(float v)
	{
#if defined(GX_ASM)
		float result = 0.0f;
		__asm
		{
			fld[v]
			fabs
			fstp[result]
		}
		return result;
#else
		return GX_CAST_S(float,fabs(v));
#endif
	}
	/// 开平方
	inline float sqrt(float v)
	{
#if defined(GX_ASM)
		float result = 0.0f;
		__asm
		{
			fld[v]
			fsqrt
			fstp[result]
		}
		return result;
#else
		return sqrtf(v);
#endif
	}
	/// 开平方的倒数
	inline float reciprocalSqrt(float v)
	{
#if defined(GX_ASM)
		float result = 0.0f;
		__asm
		{
			fld[v]
			fsqrt
			fld1
			fdivrp st(1), st
			fstp[result]
		}
		return result;
#else
		return 1.0f / sqrtf(v);
#endif
	}
	/// 正弦函数
	inline float sin(float radian)
	{
#if defined(GX_ASM)
		float result = 0.0f;
		__asm
		{
			fld[radian]
			fsin
			fstp[result]
		}
		return result;
#else
		return sinf(radian);
#endif
	}

	/// 快速正弦函数，需要 -GX_PI<angle<GX_PI
	inline float fastSin(float angle)
	{
		const float Factor1 = 4.0f / GX_PI;
		const float Factor2 = 4.0f / (GX_PI * GX_PI);
		return (Factor1 * angle) - (Factor2 * angle * abs(angle));
	}
	/// 反正弦函数
	inline float asin(float v)
	{
        return (float)::asin(v);
	}
	/// 余弦函数
	inline float cos(float radian)
	{
#if defined(GX_ASM)
		float result = 0.0f;
		__asm
		{
			fld[radian]
			fcos
			fstp[result]
		}
		return result;
#else
		return cosf(radian);
#endif
	}
	/// 反余弦函数
	inline float acos(float v)
	{
        return (float)::acos(v);
	}
	/// 正余弦函数，同时得到正弦和余弦值
	inline void sincos(float radian, float &sinvalue, float &cosvalue)
	{
#if defined(GX_ASM)
		unsigned short cwd_flag = 0;

		__asm
		{
			fstsw[cwd_flag]
		}

		int stacktop = (cwd_flag & 0x3800) >> 11;

		if (stacktop < 7)
		{
			__asm
			{
				mov eax, dword ptr[cosvalue]
					mov ebx, dword ptr[sinvalue]
					fld[radian]
					fsincos
					fstp dword ptr[eax]
					fstp dword ptr[ebx]
			}
		}
		else
		{
			float s0, s1;
			__asm
			{
				fstp[s0]
					fstp[s1]
					mov eax, dword ptr[cosvalue]
					mov ebx, dword ptr[sinvalue]
					fld[radian]
					fsincos
					fstp dword ptr[eax]
					fstp dword ptr[ebx]
					fld[s1]
					fld[s0]
			}
		}
#else
		sinvalue = sinf(radian);
		cosvalue = cosf(radian);
#endif
	}
	/// 正切函数
	inline float tan(float radian)
	{
#if defined(GX_ASM)
		float result = 0.0;

		unsigned short cwd_flag = 0;

		__asm
		{
			fstsw[cwd_flag]
		}

		int stacktop = (cwd_flag & 0x3800) >> 11;
		if (stacktop < 7)
		{
			__asm
			{
				fld[radian]
					fptan
					fstp[result]
					fstp[result]
			}
		}
		else
		{
			float s0, s1;
			__asm
			{
				fstp[s0]
					fstp[s1]
					fld[radian]
					fptan
					fstp[result]
					fstp[result]
					fld[s1]
					fld[s0]
			}
		}

		return result;
#else
		return tanf(radian);
#endif
	}
	/// 正切的倒数
	inline float cot(float radian)
	{
#if defined(GX_ASM)
		float result = 0.0;

		unsigned short cwd_flag = 0;
		__asm
		{
			fstsw[cwd_flag]
		}
		int stacktop = (cwd_flag & 0x3800) >> 11;
		if (stacktop < 7)
		{
			__asm
			{
				fld[radian]
					fptan
					fdivrp st(1), st(0)
					fstp[result]
			}
		}
		else
		{
			float s0, s1;
			__asm
			{
				fstp[s0]
					fstp[s1]
					fld[radian]
					fptan
					fdivrp st(1), st(0)
					fstp[result]
					fld[s1]
					fld[s0]
			}
		}

		return result;
#else
		return 1.0f / tanf(radian);
#endif
	}
	/// 反正切函数
	inline float atan(float radian)
	{
#if defined(GX_ASM)
		float result = 0.0;
		__asm
		{
			fld[radian]
				fpatan
				fstp[result]
		}
		return result;
#else
		return atanf(radian);
#endif

	}

	/// 反正切函数2
	inline float atan2(float x, float y)
	{
		return atan2f(x, y);
	}

	/// 取小数部分
	inline float frac(float a)
	{
		return a - (int)a;
	}

	/// 四舍五入
	inline float round(float v)
	{
		return (float)(int)(v + 0.5f);
	}

	/// 向上取整
	inline float ceil(float v)
	{
		return ceilf(v);
	}

	/// 向下取整
	inline float floor(float v)
	{
		return floorf(v);
	}

	/// 线性插值函数
	/// @param start	开始值
	/// @param end		结束值
	/// @param t		系数(0<=t<=1)
	inline float linear(float start, float end, float t) {
		return (float)((1.0f - t) * start + t * end);
	}

	/// 二次渐入插值函数
	/// @param start	开始值
	/// @param end		结束值
	/// @param t		系数(0<=t<=1)
	inline float quadraticEaseIn(float start, float end, float t) {
		return (float)((end - start)*t*t + start);
	}
	/// 二次渐出插值函数
	/// @param start	开始值
	/// @param end		结束值
	/// @param t		系数(0<=t<=1)
	inline float quadraticEaseOut(float start, float end, float t) {
		return (float)((start - end)*(t - 1.0f)*(t - 1.0f) + end);
	}
	/// 二次渐入渐出插值函数
	/// @param start	开始值
	/// @param end		结束值
	/// @param t		系数(0<=t<=1)
	inline float quadraticEaseInOut(float start, float end, float t) {
		float middle = (float)((start + end)*0.5f);
		t *= 2.0f;
		if (t <= 1.0f) {
			return quadraticEaseIn(start, middle, t);
		}
		t -= 1.0f;
		return quadraticEaseOut(middle, end, t);
	}

	guint32 randUint32();
	gint32  randInt32();
	gfloat32 randFloat32();

	/// 矩阵操作
	void matrixAdd(const float* m, float scalar, float* dst);
	void matrixAdd(const float* m1, const float* m2, float* dst);
	void matrixSubtract(const float* m1, const float* m2, float* dst);
	void matrixMultiply(const float* m, float scalar, float* dst);
	void matrixMultiply(const float* m1, const float* m2, float* dst);
	void matrixNegate(const float* m, float* dst);
	void matrixTranspose(const float* m, float* dst);

	void vector3Cross(const float* v1, const float* v2, float* dst);
	void vector4Transform(const float* m, float x, float y, float z, float w, float* dst);
	void vector4Transform(const float* m, const float* v, float* dst);
}

