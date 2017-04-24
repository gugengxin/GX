//
//  GResourceManager.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GResourceManager_h
#define GResourceManager_h

#include "GXPrefix.h"
#include "GArray.h"
#include "GBundle.h"

class GResourceManager
{
protected:
    GResourceManager();
    virtual ~GResourceManager();
public:
    
    
    
private:
    GArray<GBundle> m_Bundles;
};

#endif /* GResourceManager_h */
