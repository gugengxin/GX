//
//  GX3DAPIPre.h
//  GXGame
//
//  Created by Gu Gengxin on 2017/6/6.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef GX3DAPIPre_h
#define GX3DAPIPre_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"


namespace GX {
    typedef enum _DToplogy {
        DToplogyUnknown = -1,
        DToplogyPoints = 0,
        DToplogyLines,
        DToplogyLineStrip,
        DToplogyTriangles,
        DToplogyTriangleStrip,
    } DToplogy;
    
    typedef enum _DCullFace {
        DCullFaceNone,
        DCullFaceFront,
        DCullFaceBack,
        ///////////////
        _DCullFaceCount,
    } DCullFace;
    
    
    class DCullFacer {
    public:
        DCullFacer();
        virtual ~DCullFacer();
        
        DCullFace getCullFace() const;
        virtual void setCullFace(DCullFace v);
        
    private:
        DCullFace m_Value;
    };
}




#endif /* GX3DAPIPre_h */
