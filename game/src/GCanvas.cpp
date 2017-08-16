//
//  GCanvas.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GCanvas.h"
//Down include other h file
#include "GTex2DFont.h"
#include "GSRTexture2D.h"

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GCanvas, GObject);

GCanvas::GCanvas()
{
	m_ColorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
}

GCanvas::~GCanvas()
{
}

void GCanvas::enable2D(float width, float height)
{
    m_Matrixs[MatrixView].setIdentity();
    m_Matrixs[MatrixProjection].setOrthographic(0, width, 0, height, -1, 1);
}
void GCanvas::enable3D(float width, float height, float fovy, float zNear, float zFar)
{
    m_Matrixs[MatrixView].setIdentity();
    m_Matrixs[MatrixProjection].setPerspective(fovy, width / height, zNear, zFar);
}

void GCanvas::lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
    m_Matrixs[MatrixView].setLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void GCanvas::loadIdentity()
{
    m_Matrixs[MatrixModel].setIdentity();
}
void GCanvas::translate(float x, float y, float z)
{
    m_Matrixs[MatrixModel].translate(x, y, z);
}
void GCanvas::rotate(float angle, float x, float y, float z)
{
    m_Matrixs[MatrixModel].rotate(angle, x, y, z);
}
void GCanvas::rotateX(float angle)
{
    m_Matrixs[MatrixModel].rotateX(angle);
}
void GCanvas::rotateY(float angle)
{
    m_Matrixs[MatrixModel].rotateY(angle);
}
void GCanvas::rotateZ(float angle)
{
    m_Matrixs[MatrixModel].rotateZ(angle);
}
void GCanvas::scale(float s)
{
    m_Matrixs[MatrixModel].scale(s, s, s);
}
void GCanvas::scale(float x, float y, float z)
{
    m_Matrixs[MatrixModel].scale(x, y, z);
}
void GCanvas::pushMatrix()
{
    m_MatrixStack.add(m_Matrixs[MatrixModel]);
}
void GCanvas::popMatrix()
{
    m_Matrixs[MatrixModel] = m_MatrixStack.last();
    m_MatrixStack.removeLast();
}

const float* GCanvas::updateModelMatrix()
{
    return m_Matrixs[MatrixModel].m;
}
const float* GCanvas::updateModelViewMatrix()
{
    m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
    return m_Matrixs[MatrixMV].m;
}
const float* GCanvas::updateMVPMatrix()
{
    m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
    m_Matrixs[MatrixMVP] = m_Matrixs[MatrixProjection] * m_Matrixs[MatrixMV];
    return m_Matrixs[MatrixMVP].m;
}


GTypist::Paper::PrintGlyphSelector GCanvas::printCheck(GFont* font)
{
    if (font->isKindOfClass(GTex2DFont::gclass)) {
        return &printTex2DFontGlyph;
    }
    return NULL;
}

void GCanvas::printBegin(GPointF pos)
{
    pushMatrix();
    translate(pos.x, pos.y, 0.0f);
}

void GCanvas::printTex2DFontGlyph(GTypist::Paper* paper,GFont::Glyph* glyph,GPointF pos,GPointF offset,const GTypist::Paint* paint)
{
    GCanvas* canvas=GX_CAST_S(GCanvas*, paper);
    GTex2DFont::Glyph* realGH=GX_CAST_R(GTex2DFont::Glyph*, glyph);
    canvas->setColorMul(0, 1, 0, 1);
    GSRTexture2D::shared(true, true, GSRTexture2D::MM_None)->draw(canvas,
                                                                  realGH->getBuffer(), 0, 16,
                                                                  GSRTexture2D::IT_Float_UShort,
                                                                  realGH->getTexture(),
                                                                  GX_TRIANGLE_STRIP,
                                                                  0, 4,
                                                                  NULL);
    
    canvas->translate(offset.x, offset.y, 0.0f);
}

void GCanvas::printEnd()
{
    popMatrix();
}

