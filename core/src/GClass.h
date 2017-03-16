//
//  GClass.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GClass_h
#define GClass_h

#include "GXPrefix.h"

class GObject;

class GClass {
public:
    typedef GObject* (*Alloc)();
public:
    GClass(guint size,Alloc alloc,GClass* parent);
    ~GClass();
    
    inline guint getSize() {
        return m_Size;
    }
    inline GClass* getParent() {
        return m_Parent;
    }
public:
    bool isMemberOf(GClass* pClass);
    bool isKindOf(GClass* pClass);
public:
    GObject* alloc();
    
private:
    guint           m_Size;
    Alloc           m_Alloc;
    GClass*         m_Parent;
};

#endif /* GClass_h */
