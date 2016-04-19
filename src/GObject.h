//
//  GObject.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GObject_hpp
#define GObject_hpp

#include "GXPrefix.h"
#include "GClass.h"

class GObject {
protected:
    friend void GXRetain(GObject*);
    friend void GXRelease(GObject*);
    GObject();
    virtual ~GObject();
public:
    static GClass   gclass;
    virtual GClass* getClass();
    static GObject* alloc();
    
    const gchar* getClassName();
    bool  isMemberOfClass(GClass* pClass);
    bool  isMemberOfClass(GClass& cls);
    bool  isKindOfClass(GClass* pClass);
    bool  isKindOfClass(GClass& cls);
    
private:
    gi32 m_RefCount;
};


void GXRetain(GObject* obj);
void GXRelease(GObject* obj);



#endif /* GObject_hpp */
