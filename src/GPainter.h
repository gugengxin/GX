#pragma once
#include "GXPrefix.h"
#include "GMatrix.h"
#include "GDataArray.h"
#include "GColor.h"

class GPainter
{
public:
	typedef enum _Matrix {
		MatrixModel = 0,
		MatrixView,
		MatrixProjection,
		MatrixMV,
		MatrixMVP,

		///////////////////
		MatrixCount,
	} Matrix;
public:
	GPainter();
	~GPainter();

public:
	/// 矩阵开始2D模式
	void enable2D(float width, float height);
	/// 矩阵开始3D模式
	/// @param fovy 单位为弧度
	void enable3D(float width, float height, float fovy, float zNear, float zFar);
	/// 设置相机视图
	void lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

	/// 重置当前矩阵为单位矩阵
	void loadIdentity();
	/// 移动当前矩阵
	void translate(float x, float y, float z);
	/// 旋转当前矩阵
	/// @param angle 旋转角度,单位为弧度
	void rotate(float angle, float x, float y, float z);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	/// 缩放当前矩阵
	void scale(float s);
	void scale(float x, float y, float z);
	/// 保存当前矩阵，入栈
	void pushMatrix();
	/// 恢复保存的矩阵，出栈
	void popMatrix();

	const float* updateModelMatrix();
	const float* updateModelViewMatrix();
	const float* updateMVPMatrix();

public:
	const float* updateColorMul() {
		return &m_ColorMul.r;
	}

private:
	GMatrix4 m_Matrixs[MatrixCount];
	GPDArray<GMatrix4> m_MatrixStack;
	GColor4F m_ColorMul;
};

