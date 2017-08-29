//
//  GCanvas.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GCanvas_h
#define GCanvas_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#include "GObject.h"
#include "GMatrix.h"
#include "GDataArray.h"
#include "GColor.h"
#include "GTypist.h"
#include "GTex2DFont.h"



#include "GXGObject.h"
// Down can't include other h file

class GCanvas : public GObject, public GTypist::Paper
{
	GX_VIRTUAL_GOBJECT(GCanvas);    
public:
    virtual float getWidth()=0;
    virtual float getHeight()=0;
    virtual float getDensity()=0;
    
    /// 矩阵开始2D模式
    virtual void enable2D(gint index, float width, float height);
    /// 矩阵开始3D模式
    /// @param fovy 单位为弧度
	virtual void enable3D(gint index, float width, float height, float fovy, float zNear, float zFar);
    /// 设置相机视图
    void lookAt(gint index, float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
    
    /// 重置当前矩阵为单位矩阵
    void loadIdentity(gint index);
    /// 移动当前矩阵
    void translate(gint index, float x, float y, float z);
    /// 旋转当前矩阵
    /// @param angle 旋转角度,单位为弧度
    void rotate(gint index, float angle, float x, float y, float z);
    void rotateX(gint index, float angle);
    void rotateY(gint index, float angle);
    void rotateZ(gint index, float angle);
    /// 缩放当前矩阵
    void scale(gint index, float s);
    void scale(gint index, float x, float y, float z);
    /// 保存当前矩阵，入栈
    void pushMatrix(gint index);
    /// 恢复保存的矩阵，出栈
    void popMatrix(gint index);
    
    const float* updateModelMatrix(gint index);
    const float* updateModelViewMatrix(gint index);
    const float* updateMVPMatrix(gint index);
    guint32 getMVPMatrixID(gint index) const;
    
public:
    gint getColorMulCount();
    void setColorMul(gint index,float r,float g,float b,float a) {
        m_ColorMul[index].set(r, g, b, a);
    }
    const float* updateColorMul(gint index) {
        return &m_ColorMul[index].r;
    }
    void pushColorMul(gint index);
    void popColorMul(gint index);
    
public:
    virtual const GColor4F& getBackgroundColor() const =0;
    virtual void setBackgroundColor(float r,float g,float b,float a) =0;
#if defined(GX_METAL)
public:
    virtual void* metalNewRCE()=0;
    virtual gint metalBlendIndex()=0;
#endif
protected:
	typedef enum _Matrix {
		MatrixModel = 0,
		MatrixView,
		MatrixProjection,
		MatrixMV,
		MatrixMVP,

		///////////////////
		MatrixCount,
	} Matrix;
	inline GMatrix4& getMatrix(gint index,Matrix mid) {
		return m_Matrixs[index][mid];
	}
protected:
    virtual bool isFlipped();
    virtual GTypist::Paper::PrintGlyphSelector printCheck(GFont* font);
    virtual void printBegin(GFont* font,GPointF pos);
    static void printTex2DFontGlyph(GTypist::Paper* paper,GFont* font,GFont::Glyph* glyph,GPointF pos,GPointF offset,const GTypist::Paint* paint);
    virtual void printEnd();
private:
    GMatrix4 m_Matrixs[2][MatrixCount];
    guint32  m_MatrixID[2][MatrixCount*2];
    GPDArray<GMatrix4> m_MatrixStack[2];
    
    GColor4F m_ColorMul[2];
    GPDArray<GColor4F> m_ColorMulStack[2];
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GCanvas_h */
