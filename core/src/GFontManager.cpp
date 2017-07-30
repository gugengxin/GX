//
//  GFontManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFontManager.h"

#if __llvm__
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdocumentation"
#endif
#include <ft2build.h>
#include FT_FREETYPE_H
#if __llvm__
#pragma clang diagnostic pop
#endif
#if defined(GX_OS_APPLE)
#import <CoreText/CoreText.h>
#if defined(GX_OS_IPHONE)
#import <UIKit/UIKit.h>
#elif defined(GX_OS_MACOSX)
#import <Cocoa/Cocoa.h>
#endif
#elif defined(GX_OS_WINDOWS)
#include <Windows.h>
#endif


#if defined(GX_OS_APPLE)

typedef struct FontHeader {
    int32_t fVersion;
    uint16_t fNumTables;
    uint16_t fSearchRange;
    uint16_t fEntrySelector;
    uint16_t fRangeShift;
}FontHeader;

typedef struct TableEntry {
    uint32_t fTag;
    uint32_t fCheckSum;
    uint32_t fOffset;
    uint32_t fLength;
}TableEntry;

static uint32_t CalcTableCheckSum(const uint32_t *table, uint32_t numberOfBytesInTable) {
    uint32_t sum = 0;
    uint32_t nLongs = (numberOfBytesInTable + 3) / 4;
    while (nLongs-- > 0) {
        sum += CFSwapInt32HostToBig(*table++);
    }
    return sum;
}

/*
static uint32_t CalcTableDataRefCheckSum(CFDataRef dataRef) {
    const uint32_t *dataBuff = (const uint32_t *)CFDataGetBytePtr(dataRef);
    uint32_t dataLength = (uint32_t)CFDataGetLength(dataRef);
    return CalcTableCheckSum(dataBuff, dataLength);
}
//*/

//Reference:
//https://gist.github.com/Jyczeal/1892760

static GData* _createSystemFontData(GString* name)
{
    NSString* nsName=[[NSString alloc] initWithCharactersNoCopy:(unichar*)name->utf16String()
                                                         length:name->getLength()
                                                   freeWhenDone:NO];
    CTFontRef ctFont=CTFontCreateWithName((CFStringRef)nsName, 0.0f, NULL);
    [nsName release];
    
    if (!ctFont) {
        return NULL;
    }
    
    CGFontRef cgFont=CTFontCopyGraphicsFont(ctFont, NULL);
    
    if (!cgFont) {
        return NULL;
    }
    
    CFArrayRef tags = CGFontCopyTableTags(cgFont);
    int tableCount = (int)CFArrayGetCount(tags);
    
    size_t *tableSizes = (size_t *)malloc(sizeof(size_t) * tableCount);
    memset(tableSizes, 0, sizeof(size_t) * tableCount);
    
    BOOL containsCFFTable = NO;
    
    size_t totalSize = sizeof(FontHeader) + sizeof(TableEntry) * tableCount;
    
    for (int index = 0; index < tableCount; ++index) {
        
        //get size
        size_t tableSize = 0;
        uint32_t aTag = (uint32_t)(NSUInteger)CFArrayGetValueAtIndex(tags, index);
        
        if (aTag == 'CFF ' && !containsCFFTable) {
            containsCFFTable = YES;
        }
        
        CFDataRef tableDataRef = CGFontCopyTableForTag(cgFont, aTag);
        if (tableDataRef != NULL) {
            tableSize = CFDataGetLength(tableDataRef);
            CFRelease(tableDataRef);
        }
        totalSize += (tableSize + 3) & ~3;
        
        tableSizes[index] = tableSize;
    }
    
    GData* res=GData::alloc();
    if (res->changeBytes(totalSize)) {
        res->zeroSelf();
        
        unsigned char *stream = (unsigned char *)res->getPtr();
        char* dataStart = (char*)stream;
        char* dataPtr = dataStart;
        
        // compute font header entries
        uint16_t entrySelector = 0;
        uint16_t searchRange = 1;
        
        while (searchRange < tableCount >> 1) {
            entrySelector++;
            searchRange <<= 1;
        }
        searchRange <<= 4;
        
        uint16_t rangeShift = (tableCount << 4) - searchRange;
        
        // write font header (also called sfnt header, offset subtable)
        FontHeader* offsetTable = (FontHeader*)dataPtr;
        
        //OpenType Font contains CFF Table use 'OTTO' as version, and with .otf extension
        //otherwise 0001 0000
        offsetTable->fVersion = containsCFFTable ? 'OTTO' : CFSwapInt16HostToBig(1);
        offsetTable->fNumTables = CFSwapInt16HostToBig((uint16_t)tableCount);
        offsetTable->fSearchRange = CFSwapInt16HostToBig((uint16_t)searchRange);
        offsetTable->fEntrySelector = CFSwapInt16HostToBig((uint16_t)entrySelector);
        offsetTable->fRangeShift = CFSwapInt16HostToBig((uint16_t)rangeShift);
        
        dataPtr += sizeof(FontHeader);
        
        // write tables
        TableEntry* entry = (TableEntry*)dataPtr;
        dataPtr += sizeof(TableEntry) * tableCount;
        
        for (int index = 0; index < tableCount; ++index) {
            
            uint32_t aTag = (uint32_t)(NSUInteger)CFArrayGetValueAtIndex(tags, index);
            CFDataRef tableDataRef = CGFontCopyTableForTag(cgFont, aTag);
            size_t tableSize = CFDataGetLength(tableDataRef);
            
            memcpy(dataPtr, CFDataGetBytePtr(tableDataRef), tableSize);
            
            entry->fTag = CFSwapInt32HostToBig((uint32_t)aTag);
            entry->fCheckSum = CFSwapInt32HostToBig(CalcTableCheckSum((uint32_t *)dataPtr, (uint32_t)tableSize));
            
            uint32_t offset = (uint32_t)((NSUInteger)dataPtr - (NSUInteger)dataStart);
            entry->fOffset = CFSwapInt32HostToBig((uint32_t)offset);
            entry->fLength = CFSwapInt32HostToBig((uint32_t)tableSize);
            dataPtr += (tableSize + 3) & ~3;
            ++entry;
            
            CFRelease(tableDataRef);
        }
    }
    else {
        GO::release(res);
        res=NULL;
    }
    
    CFRelease(cgFont);
    free(tableSizes);
    return res;
}

#elif defined(GX_OS_WINDOWS)


#endif





#define M_FT_LIBRARY() GX_CAST_R(FT_Library, m_FTLibrary)


GFontManager* GFontManager::shared()
{
    static GFontManager g_Obj;
    return &g_Obj;
}


GFontManager::GFontManager()
{
#if defined(GX_OS_IPHONE)
    NSArray *familyNames = [UIFont familyNames];
    for (NSString* fyn in familyNames) {
        NSArray* fontNames=[UIFont fontNamesForFamilyName:fyn];
        if ([fontNames count]<=0) {
            GString* key=GS::chars([fyn UTF8String]);
            m_SystemFontNames.set(key, key);
        }
        else {
            for (NSString* str in fontNames) {
                GString* key=GS::chars([str UTF8String]);
                m_SystemFontNames.set(key, key);
            }
        }
    }
#elif defined(GX_OS_MACOSX)
    NSArray* arr=[[NSFontManager sharedFontManager] availableFonts];
    for (NSString* str in arr) {
        GString* key=GS::chars([str UTF8String]);
        m_SystemFontNames.set(key, key);
    }
#elif defined(GX_OS_ANDROID)
    
#elif defined(GX_OS_WINDOWS)
	//::EnumFontFamilies
    //::GetFontData
    //::GetTextMetrics tmPitchAndFamily&TMPF_TRUETYPE
#endif
    
    FT_Init_FreeType(GX_CAST_R(FT_Library*, &m_FTLibrary));
}

GFontManager::~GFontManager()
{
    FT_Done_FreeType(M_FT_LIBRARY());
}

GMap<GString, GObject>* GFontManager::getMap(gint index)
{
    return &m_Maps[index];
}

void GFontManager::didReceivedMemoryWarning()
{
    m_FTDataMap.removeAll();
}

GFTFont* GFontManager::loadFTFont(GString* name, gint32 size, gint32 outlineSize)
{
    if (size<=0) {
        size=12;
    }
    if (outlineSize<0) {
        outlineSize=0;
    }
    GString* key=GString::alloc();
    key->format("%@_%@_%@").arg(name).arg(size).arg(outlineSize).end();
    
    GFTFont* res=GX_CAST_R(GFTFont*, findInMap(MapFT, key));
    if (!res) {
        GData* data=m_FTDataMap.get(name);
        if (!data) {
            GObject* sfn=m_SystemFontNames.get(name);
            if (sfn) {//系统字体列表里有
#if defined(GX_OS_APPLE)
                data=_createSystemFontData(name);
#endif
            }
            else {
                GBundle* bundle=NULL;
                GReader* reader=openReader(name, bundle);
                if (reader) {
                    data=reader->readAllToData();
                    closeReader(reader, bundle);
                }
            }
            if (data && data->getBytes()>0) {
                m_FTDataMap.set(name, data);
            }
        }
        
        if (data && data->getBytes()>0) {
            res=GFTFont::alloc();
            if(res->create(data, size, outlineSize)) {
				addToMap(MapFT, key, res);
                GO::autorelease(res);
            }
            else {
                GO::release(res);
                res=NULL;
            }
        }
    }
    
    GO::release(key);
    return res;
}


