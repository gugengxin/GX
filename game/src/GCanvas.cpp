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
    for (gint i=0; i<sizeof(m_ColorMul)/sizeof(m_ColorMul[0]); i++) {
        m_ColorMul[i].set(1.0f, 1.0f, 1.0f, 1.0f);
    }
    memset(m_MatrixID, 0, sizeof(m_MatrixID));
}

GCanvas::~GCanvas()
{
}

void GCanvas::enable2D(float width, float height)
{
    m_Matrixs[MatrixView].setIdentity();
    ++m_MatrixID[MatrixView*2+0];
    m_Matrixs[MatrixProjection].setOrthographic(0, width, 0, height, -1, 1);
    ++m_MatrixID[MatrixProjection*2+0];
}
void GCanvas::enable3D(float width, float height, float fovy, float zNear, float zFar)
{
    m_Matrixs[MatrixView].setIdentity();
    ++m_MatrixID[MatrixView*2+0];
    m_Matrixs[MatrixProjection].setPerspective(fovy, width / height, zNear, zFar);
    ++m_MatrixID[MatrixProjection*2+0];
}

void GCanvas::lookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
    m_Matrixs[MatrixView].setLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
    ++m_MatrixID[MatrixView*2+0];
}

void GCanvas::loadIdentity()
{
    m_Matrixs[MatrixModel].setIdentity();
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::translate(float x, float y, float z)
{
    m_Matrixs[MatrixModel].translate(x, y, z);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::rotate(float angle, float x, float y, float z)
{
    m_Matrixs[MatrixModel].rotate(angle, x, y, z);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::rotateX(float angle)
{
    m_Matrixs[MatrixModel].rotateX(angle);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::rotateY(float angle)
{
    m_Matrixs[MatrixModel].rotateY(angle);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::rotateZ(float angle)
{
    m_Matrixs[MatrixModel].rotateZ(angle);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::scale(float s)
{
    m_Matrixs[MatrixModel].scale(s, s, s);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::scale(float x, float y, float z)
{
    m_Matrixs[MatrixModel].scale(x, y, z);
    ++m_MatrixID[MatrixModel*2+0];
}
void GCanvas::pushMatrix()
{
    m_MatrixStack.push(m_Matrixs[MatrixModel]);
}
void GCanvas::popMatrix()
{
    m_Matrixs[MatrixModel] = m_MatrixStack.pop();
}

const float* GCanvas::updateModelMatrix()
{
    m_MatrixID[MatrixModel*2+1]=m_MatrixID[MatrixModel*2+0];
    return m_Matrixs[MatrixModel].m;
}
const float* GCanvas::updateModelViewMatrix()
{
    if (m_MatrixID[MatrixModel*2+1]!=m_MatrixID[MatrixModel*2+0] ||
        m_MatrixID[MatrixView*2+1]!=m_MatrixID[MatrixView*2+0]) {
        m_MatrixID[MatrixModel*2+1]=m_MatrixID[MatrixModel*2+0];
        m_MatrixID[MatrixView*2+1]=m_MatrixID[MatrixView*2+0];
        
        m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
        ++m_MatrixID[MatrixMV*2+0];
    }
    return m_Matrixs[MatrixMV].m;
}
const float* GCanvas::updateMVPMatrix()
{
    if (m_MatrixID[MatrixModel*2+1]!=m_MatrixID[MatrixModel*2+0] ||
        m_MatrixID[MatrixView*2+1]!=m_MatrixID[MatrixView*2+0] ||
        m_MatrixID[MatrixProjection*2+1]!=m_MatrixID[MatrixProjection*2+0]) {
        m_MatrixID[MatrixModel*2+1]=m_MatrixID[MatrixModel*2+0];
        m_MatrixID[MatrixView*2+1]=m_MatrixID[MatrixView*2+0];
        m_MatrixID[MatrixProjection*2+1]=m_MatrixID[MatrixProjection*2+0];
        
        m_Matrixs[MatrixMV] = m_Matrixs[MatrixView] * m_Matrixs[MatrixModel];
        ++m_MatrixID[MatrixMV*2+0];
        
        m_Matrixs[MatrixMVP] = m_Matrixs[MatrixProjection] * m_Matrixs[MatrixMV];
        ++m_MatrixID[MatrixMVP*2+0];
    }
    
    return m_Matrixs[MatrixMVP].m;
}

guint32 GCanvas::getMVPMatrixID() const
{
    return m_MatrixID[MatrixMVP*2+0];
}

gint GCanvas::getColorMulCount()
{
    return sizeof(m_ColorMul)/sizeof(m_ColorMul[0]);
}

void GCanvas::pushColorMul(gint index)
{
    m_ColorMulStack[index].push(m_ColorMul[index]);
}
void GCanvas::popColorMul(gint index)
{
    m_ColorMul[index]=m_ColorMulStack[index].pop();
}


bool GCanvas::isFlipped()
{
    return false;
}

GTypist::Paper::PrintGlyphSelector GCanvas::printCheck(GFont* font)
{
    if (font->isKindOfClass(GTex2DFont::gclass)) {
        return &printTex2DFontGlyph;
    }
    return NULL;
}

void GCanvas::printBegin(GFont* font,GPointF pos)
{
    pushMatrix();
    pushColorMul(0);
    translate(0, getHeight(), 0);
    translate(pos.x, -pos.y, 0.0f);
    scale(1.0f/font->getDensity());
    translate(0.0f, -font->getAscender()/64.0f, 0.0f);
}

void GCanvas::printTex2DFontGlyph(GTypist::Paper* paper,GFont* font,GFont::Glyph* glyph,GPointF pos,GPointF offset,const GTypist::Paint* paint)
{
    GCanvas* canvas=GX_CAST_S(GCanvas*, paper);
    canvas->translate(offset.x, -offset.y, 0.0f);
    
    GTex2DFont::Glyph* realGH=GX_CAST_R(GTex2DFont::Glyph*, glyph);
    if (!realGH->isBlank()) {
        canvas->setColorMul(0, 0, 1, 0, 1);
        GSRTexture2D::shared(true, true, GSRTexture2D::MM_None)->draw(canvas,
                                                                      realGH->getBuffer(), 0, sizeof(float)*3+sizeof(guint16)*2,
                                                                      GSRTexture2D::IT_Float_UShort,
                                                                      realGH->getTexture(),
                                                                      GX_TRIANGLE_STRIP,
                                                                      0, 4,
                                                                      NULL);
    }
}

void GCanvas::printEnd()
{
    popColorMul(0);
    popMatrix();
}

