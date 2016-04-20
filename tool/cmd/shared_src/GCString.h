#pragma once

#include "GCShared.h"
#include <string>
#ifdef GC_OS_MICROSOFT
#include <tchar.h>
#define GC_PATH_IS_WCHAR
#else

#ifndef _tfopen
#define _tfopen			fopen
#endif
#ifndef _T
#define _T(x) x
#define TCHAR char
#endif

#endif

namespace GC {
    
    enum SEncoding
    {
        SEC_Utf8,
        SEC_Gb2312,
        
        SEC_Utf16,
    };
    
    class NString : public std::string {
    public:
        bool getHasBOM() {
            return m_HasBOM;
        }
        void setHasBOM(bool v) {
            m_HasBOM=v;
        }
        SEncoding getEncoding() {
            return m_Encoding;
        }
        void SetEncoding(SEncoding v) {
            m_Encoding=v;
        }
    private:
        bool m_HasBOM;
        SEncoding m_Encoding;
    };
	
    class WString : public std::wstring {
    public:
        SEncoding getEncoding() {
            return m_Encoding;
        }
        void SetEncoding(SEncoding v) {
            m_Encoding=v;
        }
    private:
        SEncoding m_Encoding;
    };
    
#ifdef GC_PATH_IS_WCHAR
    typedef WString TString;
#else
    typedef NString TString;
#endif
    typedef TString Path;

    extern const int utf8BOM_Bytes;
    extern const unsigned char utf8BOM[];
    
    bool readFileString(const TCHAR* filePath,SEncoding guessEC,NString& strOut);
    bool readFileString(const TCHAR* filePath,SEncoding guessEC,WString& strOut);
    
    bool writeFileString(const TCHAR* filePath, NString& str);
    bool writeFileString(const TCHAR* filePath, WString& str);


	void replaceString(NString& str, const char* strFrom, const char* strTo, int idxStart = 0, int idxCount = 0);
	void replaceString(WString& str, const wchar_t* strFrom, const wchar_t* strTo, int idxStart=0, int idxCount=0);

	void replaceString(NString& str, const char* strFromPre, const char* strFromSuf, const char* strTo, int idxStart = 0, int idxCount = 0);
	void replaceString(WString& str, const wchar_t* strFromPre, const wchar_t* strFromSuf, const wchar_t* strTo, int idxStart = 0, int idxCount = 0);

}