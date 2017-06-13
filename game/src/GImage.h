//
//  GImage.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GImage_h
#define GImage_h

#include "GXPrefix.h"
#include "GX3DAPI.h"
#include "GObject.h"
#include "GGraphBase.h"
#include "GTexture2D.h"
#include "GVector.h"
#include "GCanvas.h"



#include "GXGObject.h"
// Down can't include other h file

class GImage : public GGraphBase
{
	GX_GOBJECT(GImage);
protected:
#pragma pack(1)
    class Data {
    public:
        GVector2 position;
        GVector2 texcoord;
    };
#pragma pack()
public:
    GVector2 getPosition(gint index);
    void setPosition(gint index,const GVector2 v);
    void setPosition(gint index,float x, float y);
    GVector2 getTexcoord(gint index);
    void setTexcoord(gint index,const GVector2 v);
    void setTexcoord(gint index,float x, float y);
    void setDataPT(gint index,GVector2 pos,GVector2 tc);
    void setDataPT(gint index,float posX,float posY,float tcX,float tcY);
    GTexture2D* getTexture() const;
    void setTexture(GTexture2D* tex);
    float getScale() const;
    void setScale(float v);
    gint getMode() const;
    void setMode(gint v);
    GX::DToplogy getToplogy() const;
    void setToplogy(GX::DToplogy v);
public:
    void draw(GContext& context,GCanvas* canvas);
private:
    GTexture2D* m_Tex2D;
    float       m_Scale;
    gint        m_Mode;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GImage_h */
