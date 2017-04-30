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
    friend class GAppBundle;
	friend class GBundle;
    friend class GZipReader;
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
        Formater& arg(guchar v,gint count=1);
        Formater& arg(gwchar v,gint count=1);
        
        
        void end();
    private:
        GString* m_String;
        gint m_Cursor;
        gint m_CursorEnd;
    };
public:
    virtual bool isEqual(GObject* obj);
    
public:
    gint getLength();
    virtual guint getHash();
    guchar at(gint idx);
    void remove(gint idx, gint len);
    void clear();
    guchar* prepareBuffer(gint len);
    void cutOff(gint len);
public:
    const gchar* utf8String();
    const gwchar* unicodeString();
    const gtchar* pathString();
    
public:
    void set(gchar v, gint count=1);
    void append(gchar v, gint count=1);
    void insert(gint idx, gchar v, gint count=1);
    void replace(gint idx, gint lenR, gchar v, gint count=1);

	void set(guchar v, gint count = 1);
	void append(guchar v, gint count = 1);
	void insert(gint idx, guchar v, gint count = 1);
	void replace(gint idx, gint lenR, guchar v, gint count = 1);
    
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

	void set(const guchar* v, gint len = -1, gint count = 1);
	void append(const guchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const guchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, const guchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR,
		guchar preChar, gint preCount,
		guchar sufChar, gint sufCount,
		const guchar* v, gint len = -1, gint count = 1);
    
    void set(const gwchar* v, gint len = -1, gint count = 1);
    void append(const gwchar* v, gint len = -1, gint count = 1);
    void insert(gint idx, const gwchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR, const gwchar* v, gint len = -1, gint count = 1);
    void replace(gint idx, gint lenR,
                 gwchar preChar, gint preCount,
                 gwchar sufChar, gint sufCount,
                 const gwchar* v, gint len = -1, gint count = 1);
    
    void set(GString* v, gint count = 1);
    void append(GString* v, gint count = 1);
    void insert(gint idx, GString* v, gint count = 1);
    void replace(gint idx, gint lenR, GString* v, gint count = 1);
    
public:
    void setInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertInt16(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertUint16(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setFloat(gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void appendFloat(gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void insertFloat(gint idx, gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceFloat(gint idx, gint lenR, gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    
    Formater format(const gchar* fmt, gint len = -1);
    Formater appendFormat(const gchar* fmt, gint len = -1);
    Formater insertFormat(gint idx, const gchar* fmt, gint len = -1);
    Formater replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len = -1);
    
public:
	guchar pathSeparator();
	bool firstIsSeparator();
    bool lastIsSeparator();
    void appendPathComponent(const gchar* component, gint len = -1);
	void appendPathComponent(const guchar* component, gint len = -1);
    void appendPathComponent(const gwchar* component, gint len = -1);
	void appendPathComponent(GString* component);
    
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
    gint getCStringLength(GX::StringEncoding se);
    const void* getCString(GX::StringEncoding se);
    
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
