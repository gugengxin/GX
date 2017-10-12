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
        Initializer(const GClass* pClass);
        Initializer();
        ~Initializer();
    };
    friend class Initializer;
private:
    static const GClass* map[163];
    static void registerToMap(const GClass* pClass);
public:
    static const GClass* findInMap(GOWHash::Code nameCode);
    static const GClass* findInMap(const char* name);
    static const GClass* findInMap(const char* name, gint len);
    
    static GObject* allocObject(GOWHash::Code nameCode);
    static GObject* allocObject(const char* name);
    static GObject* allocObject(const char* name, gint len);
public:
    GClass(guint size,Alloc alloc,const GClass* parent);
    GClass(const char* name,guint size,Alloc alloc,const GClass* parent);
    ~GClass();
    
    const char* getName() const {
        return m_Name;
    }
    inline guint getSize() const {
        return m_Size;
    }
    inline const GClass* getParent() const {
        return m_Parent;
    }
public:
    bool isMemberOf(const GClass* pClass) const;
    bool isKindOf(const GClass* pClass) const;
public:
    GObject* allocObject() const;
private:
    const char*     m_Name;
    GOWHash::Code   m_NameCode;
    guint           m_Size;
    Alloc           m_Alloc;
    const GClass*   m_Parent;
    const GClass*   m_Next;
};

#endif /* GClass_h */
