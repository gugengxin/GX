#include "GPainter.h"


GPainter::GPainter()
{
}


GPainter::~GPainter()
{
}

void GPainter::enable2D(float width, float height)
{
	m_Matrixs[MatrixView].setIdentity();
	m_Matrixs[MatrixProjection].setOrthographic(0, width, 0, height, -1, 1);
}
void GPainter::enable3D(float width, float height, float fovy, float zNear, float zFar)
{
	m_Matrixs[MatrixView].setIdentity();
	m_Matrixs[MatrixProjection].setPerspective(fovy, width / height, zNear, zFar);
}

void GPainter::lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_Matrixs[MatrixView].setLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void GPainter::loadIdentity()
{
	m_Matrixs[MatrixModel].setIdentity();
}
void GPainter::translate(float x, float y, float z)
{
	m_Matrixs[MatrixModel].translate(x, y, z);
}
void GPainter::rotate(float angle, float x, float y, float z)
{
	m_Matrixs[MatrixModel].rotate(angle, x, y, z);
}
void GPainter::rotateX(float angle)
{
	m_Matrixs[MatrixModel].rotateX(angle);
}
void GPainter::rotateY(float angle)
{
	m_Matrixs[MatrixModel].rotateY(angle);
}
void GPainter::rotateZ(float angle)
{
	m_Matrixs[MatrixModel].rotateZ(angle);
}
void GPainter::scale(float s)
{
	m_Matrixs[MatrixModel].scale(s, s, s);
}
void GPainter::scale(float x, float y, float z)
{
	m_Matrixs[MatrixModel].scale(x, y, z);
}
void GPainter::pushMatrix()
{
	m_MatrixStack.add(m_Matrixs[MatrixModel]);
}
void GPainter::popMatrix()
{
	m_Matrixs[MatrixModel] = m_MatrixStack.last();
	m_MatrixStack.removeLast();
}

const float* GPainter::updateModelMatrix()
{
	return m_Matrixs[MatrixModel].m;
}
const float* GPainter::updateModelViewMatrix()
{
	m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
	return m_Matrixs[MatrixMV].m;
}
const float* GPainter::updateMVPMatrix()
{
	m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
	m_Matrixs[MatrixMVP] = m_Matrixs[MatrixProjection] * m_Matrixs[MatrixMV];
	return m_Matrixs[MatrixMVP].m;
}
