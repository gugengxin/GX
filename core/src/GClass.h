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
#include "GOWHash.h"

class GObject;

class GClass {
public:
    typedef GObject* (*Alloc)();
public:
    class Initializer {
    public:
        Initializer(GClass* pClass);
        Initializer();
        ~Initializer();
    };
    friend class Initializer;
private:
    static GClass* map[163];
    static void registerToMap(GClass* pClass);
public:
    static GClass* findInMap(GOWHash::Code nameCode);
    static GClass* findInMap(const char* name);
    static GClass* findInMap(const char* name, gint len);
    
    static GObject* allocObject(GOWHash::Code nameCode);
    static GObject* allocObject(const char* name);
    static GObject* allocObject(const char* name, gint len);
public:
    GClass(guint size,Alloc alloc,GClass* parent);
    GClass(const char* name,guint size,Alloc alloc,GClass* parent);
    ~GClass();
    
    const char* getName() {
        return m_Name;
    }
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
    GObject* allocObject();
private:
    const char*     m_Name;
    GOWHash::Code   m_NameCode;
    guint           m_Size;
    Alloc           m_Alloc;
    GClass*         m_Parent;
    GClass*         m_Next;
};

#endif /* GClass_h */
