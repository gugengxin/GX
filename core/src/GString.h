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
    friend class GBundle;
    friend class GFileBundle;
    friend class GZipBundle;
    friend class GAppBundle;
    friend class GZipReader;
    GX_GOBJECT(GString);
public:
    class Formater {
        friend class GString;
    private:
        Formater(GString* str, gint cursor, gint cursorEnd);
        inline GString* getString() const {
            return m_String;
        }
        inline gint getCursor() const {
            return m_Cursor;
        }
        bool moveCursor();
        gint replaceStart();
        void replaceEnd(gint lastLen);
    public:
        Formater& arg(gchar v,gint count=1);
        Formater& arg(guchar v,gint count=1);
        Formater& arg(gwchar v,gint count=1);
        
        Formater& arg(const gchar* v, gint len = -1, gint count = 1);
        Formater& arg(const guchar* v, gint len = -1, gint count = 1);
        Formater& arg(const gwchar* v, gint len = -1, gint count = 1);
        
        Formater& arg(gchar preChar, gint preCount,
                      gchar sufChar, gint sufCount,
                      const gchar* v, gint len=-1, gint count=1);
        Formater& arg(guchar preChar, gint preCount,
                      guchar sufChar, gint sufCount,
                      const guchar* v, gint len = -1, gint count = 1);
        Formater& arg(gwchar preChar, gint preCount,
                      gwchar sufChar, gint sufCount,
                      const gwchar* v, gint len = -1, gint count = 1);
        
        Formater& arg(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
        Formater& arg(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
        
        Formater& arg(GObject* v, gint count=1);
        
        void end();
    private:
        GString* m_String;
        gint m_Cursor;
        gint m_CursorEnd;
    };
public:
    static GString* chars(const gchar* str, gint len=-1);
    static GString* chars(const guchar* str, gint len=-1);
    static GString* chars(const gwchar* str, gint len=-1);
    static GString* number(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    static GString* number(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
public:
    virtual guint getHash();
    virtual bool isEqual(GObject* obj);
    virtual GString* description();
    
public:
    gint getLength();
    guchar at(gint idx);
    void remove(gint idx, gint len);
    void clear();
    guchar* prepareBuffer(gint len);
    void cutOff(gint len);
public:
    const gchar* utf8String();
    const guchar* utf16String();
    const gwchar* unicodeString();
    const gtchar* pathString();
    
public:
    void setChar(gchar v, gint count=1);
    void appendChar(gchar v, gint count=1);
    void insertChar(gint idx, gchar v, gint count=1);
    void replaceChar(gint idx, gint lenR, gchar v, gint count=1);

	void setChar(guchar v, gint count = 1);
	void appendChar(guchar v, gint count = 1);
	void insertChar(gint idx, guchar v, gint count = 1);
	void replaceChar(gint idx, gint lenR, guchar v, gint count = 1);
    
    void setChar(gwchar v, gint count=1);
    void appendChar(gwchar v, gint count=1);
    void insertChar(gint idx, gwchar v, gint count=1);
    void replaceChar(gint idx, gint lenR, gwchar v, gint count=1);
    
    void setChars(const gchar* v, gint len = -1, gint count = 1);
    void appendChars(const gchar* v, gint len = -1, gint count = 1);
    void insertChars(gint idx, const gchar* v, gint len = -1, gint count = 1);
    void replaceChars(gint idx, gint lenR, const gchar* v, gint len = -1, gint count = 1);
    void replaceChars(gint idx, gint lenR,
                 gchar preChar, gint preCount,
                 gchar sufChar, gint sufCount,
                 const gchar* v, gint len=-1, gint count=1);

	void setChars(const guchar* v, gint len = -1, gint count = 1);
	void appendChars(const guchar* v, gint len = -1, gint count = 1);
	void insertChars(gint idx, const guchar* v, gint len = -1, gint count = 1);
	void replaceChars(gint idx, gint lenR, const guchar* v, gint len = -1, gint count = 1);
	void replaceChars(gint idx, gint lenR,
		guchar preChar, gint preCount,
		guchar sufChar, gint sufCount,
		const guchar* v, gint len = -1, gint count = 1);
    
    void setChars(const gwchar* v, gint len = -1, gint count = 1);
    void appendChars(const gwchar* v, gint len = -1, gint count = 1);
    void insertChars(gint idx, const gwchar* v, gint len = -1, gint count = 1);
    void replaceChars(gint idx, gint lenR, const gwchar* v, gint len = -1, gint count = 1);
    void replaceChars(gint idx, gint lenR,
                 gwchar preChar, gint preCount,
                 gwchar sufChar, gint sufCount,
                 const gwchar* v, gint len = -1, gint count = 1);
    
    void setString(GString* v, gint count = 1);
    void appendString(GString* v, gint count = 1);
    void insertString(gint idx, GString* v, gint count = 1);
    void replaceString(gint idx, gint lenR, GString* v, gint count = 1);
    
public:
    void setNumber(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setNumber(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void appendNumber(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void insertNumber(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    void replaceNumber(gint idx, gint lenR, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
    
    void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    void replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
    
    Formater format(const gchar* fmt, gint len = -1);
    Formater appendFormat(const gchar* fmt, gint len = -1);
    Formater insertFormat(gint idx, const gchar* fmt, gint len = -1);
    Formater replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len = -1);
    
public:
	static guchar pathSeparator();
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

typedef GString GS;

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GString_h */
