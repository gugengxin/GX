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
        GVector3 position;
        GVector2 texcoord;
    };
#pragma pack()
public:
    GTexture2D* getTexture() const;
    void setTexture(GTexture2D* tex);
    float getScale() const;
    void setScale(float v);
public:
    void draw(GContext& context,GCanvas* canvas);
private:
    GTexture2D* m_Tex2D;
    float       m_Scale;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GImage_h */
