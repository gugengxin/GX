//
//  GString.h
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GString_h
#define GString_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GDataArray.h"
#include "GOWHash.h"
#include "GXEncoding.h"
#include "GSerialize.h"


#include "GXGObject.h"
// Down can't include other h file

class GString : public GObject, public GSerialize, public GUnserialize {
    friend class GZipBundle;
    friend class GFileBundle;
    GX_GOBJECT(GString);
public:
    class Formater {
        friend class GString;
    private:
        Formater(GString* str, gint cursor, gint cursorEnd);
        inline GString* getString() {
            return m_String;
        }
        inline gint getCursor() {
            return m_Cursor;
        }
        bool moveCursor();
        gint replaceStart();
        void replaceEnd(gint lastLen);
    public:
        Formater& arg(gchar v,gint count=1);
        Formater& arg(gwchar v,gint count=1);
    private:
        GString* m_String;
        gint m_Cursor;
        gint m_CursorEnd;
    };
public:
    virtual bool isEqual(GObject* obj);
    
    gint getLength();
    guint getHash();
    guchar at(gint idx);
    void remove(gint idx, gint len);
    void clear();
    guchar* prepareBuffer(gint len);
    void cutOff(gint len);
    
public:
    void set(gchar v, gint count=1);
    void append(gchar v, gint count=1);
    void insert(gint idx, gchar v, gint count=1);
    void replace(gint idx, gint lenR, gchar v, gint count=1);
    
    void set(gwchar v, gint count=1);
    void append(gwchar v, gint count=1);
    void insert(gint idx, gwchar v, gint count=1);
    void replace(gint idx, gint lenR, gwchar v, gint count=1);
    
    void set(const gchar* v, gint len = -1, gint count = 1);
    void append(const gchar* v, gint len = -1, gint count = 1);
    void insert(gint idx, const gchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR, const gchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR,
                 gchar preChar, gint preCount,
                 gchar sufChar, gint sufCount,
                 const gchar* v, gint len=-1, gint count=1);
    
    void set(const gwchar* v, gint len = -1, gint count = 1);
    void append(const gwchar* v, gint len = -1, gint count = 1);
    void insert(gint idx, const gwchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR, const gwchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR,
                 gwchar preChar, gint preCount,
                 gwchar sufChar, gint sufCount,
                 const gwchar* v, gint len = -1, gint count = 1);
public:
    void setInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertInt16(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertUint16(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    
    void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    
    void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    void replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
    
    void setFloat(gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void appendFloat(gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void insertFloat(gint idx, gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    void replaceFloat(gint idx, gint lenR, gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
    
    void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
    void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
    void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
    void replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
    
    Formater format(const gchar* fmt, gint len = -1);
    Formater appendFormat(const gchar* fmt, gint len = -1);
    Formater insertFormat(gint idx, const gchar* fmt, gint len = -1);
    Formater replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len = -1);
    
public:
    bool lastIsSeparator();
    void appendPathComponent(const gchar* component, gint len = -1);
    void appendPathComponent(const gwchar* component, gint len = -1);
    
protected:
    inline guint32 getOWHashA() {
        return m_OWHash.codeA;
    }
    inline guint32 getOWHashB() {
        return m_OWHash.codeB;
    }
    inline guint32 getOWHashC() {
        return m_OWHash.codeC;
    }
    
    void setCStringEnd();
    void modifyDone();
    
protected:
    typedef enum _SKey {
        SKBuf = 1,
    } SKey;
protected:
    virtual const GX::UUID& seGetUUID();
    virtual gint seGetBytes();
    virtual gint seEncodeFields(GEncoder& coder);
    
protected:
    virtual const GX::UUID& ueGetUUID();
    virtual gint ueDecodeField(GDecoder& coder, guint32 key, guint32 len);///返回<0失败 0没有此Key >0成功
    
private:
    GPieceDataArray<guchar,sizeof(guchar)*32> m_Buffer;
    GOWHash::Code m_OWHash;
    GX::Data            m_OutBuf;
    GX::StringEncoding  m_OutBufSE;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GString_h */
