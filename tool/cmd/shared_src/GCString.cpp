#define _CRT_SECURE_NO_WARNINGS
#include "GCString.h"
#include <stdarg.h>
#include <stdlib.h>

namespace GC {
    
    const int Utf8_BOM_Bytes=3;
    const unsigned char Utf8_BOM[Utf8_BOM_Bytes]={(const unsigned char)0xEF,(const unsigned char)0xBB,(const unsigned char)0xBF};
    
    
    static void* ReadFileData(const TCHAR* filePath,int& lenOut)
    {
        void* res = NULL;
        int outLen=-1;
        
        FILE* fp = _tfopen(filePath, _T("rb"));
        if (fp) {
            fseek(fp, 0, SEEK_END);
            outLen = (int)ftell(fp);
            fseek(fp, 0, SEEK_SET);
            
            if (outLen > 0) {
                res = malloc(outLen);
                if(fread(res, 1, outLen, fp)!=outLen) {
                    free(res);
                    res=NULL;
                    outLen=-1;
                }
            }
            fclose(fp);
        }
        lenOut=outLen;
        return res;
    }
    
    bool ReadFileToString(const TCHAR* filePath,SEncoding guessEC,NString& strOut)
    {
        int len;
        void* p=ReadFileData(filePath, len);
        
        if (len>=0) {
            
            if (len==0 || !p) {
                strOut.append("");
                strOut.setHasBOM(false);
                strOut.SetEncoding(guessEC);
            }
            else {
                if (len>=Utf8_BOM_Bytes && memcmp(Utf8_BOM, p, Utf8_BOM_Bytes)==0) {
                    strOut.setHasBOM(true);
                    strOut.SetEncoding(SEC_Utf8);
                    strOut.append(((char*)p)+Utf8_BOM_Bytes,len-Utf8_BOM_Bytes);
                }
                else {
                    strOut.setHasBOM(false);
                    strOut.SetEncoding(guessEC);
                    strOut.append((char*)p,len);
                }
            }
            if (p) {
                free(p);
            }
            return true;
        }
        return false;
    }
    bool ReadFileToString(const TCHAR* filePath,SEncoding guessEC,WString& strOut)
    {
        int len;
        void* p=ReadFileData(filePath, len);
        
        if (len>=0) {
            strOut.SetEncoding(SEC_Utf16);
            if (len==0) {
                strOut.append(L"");
            }
            else if(p) {
                strOut.append((wchar_t*)p,len);
            }
            if (p) {
                free(p);
            }
            return true;
        }
        return false;
    }

	bool WriteFileData(const TCHAR* filePath, const void* data, int len, ...)
	{
		FILE* fp = _tfopen(filePath, _T("wb"));
		if (!fp) {
			return false;
		}
		va_list va;
		va_start(va, len);
		const void* dataTemp = data;
		int dataTempLen = len;
		while (true)
		{
			fwrite(dataTemp, dataTempLen, 1, fp);

			dataTemp = va_arg(va, const void*);
			if (dataTemp) {
				dataTempLen = va_arg(va, int);
			}
			else {
				break;
			}
		}
		va_end(va);
		fclose(fp);
		return true;
	}
    
    bool WriteFileString(const TCHAR* filePath, NString& str)
    {
        if (str.getHasBOM()) {
            return WriteFileData(filePath, Utf8_BOM, Utf8_BOM_Bytes, str.data(), (int)str.size(), NULL);
        }
        else {
            return WriteFileData(filePath, str.data(), (int)str.size(), NULL);
        }
    }
    
    bool WriteFileString(const TCHAR* filePath, WString& str)
    {
        return WriteFileData(filePath, str.data(), (int)str.size(),NULL);
    }

	void ReplaceString(WString& str, const wchar_t* strFrom, const wchar_t* strTo, int idxStart, int idxCount)
	{
		int flen = (int)wcslen(strFrom);
		int tlen = (int)wcslen(strTo);
		if (flen > 0) {
			int idx = 0;
            int num=-1;
			while (true)
			{
				idx = (int)str.find(strFrom, idx);
				if (idx >= 0) {
                    num++;
                    if (idxCount<=0 || (num>=idxStart && num<idxStart+idxCount)) {
                        str.replace(idx, flen, strTo);
                    }
					idx += tlen;
				}
				else {
					break;
				}
			}
		}
	}

	void ReplaceString(NString& str, const char* strFrom, const char* strTo, int idxStart, int idxCount)
	{
		int flen = (int)strlen(strFrom);
		int tlen = (int)strlen(strTo);
		if (flen > 0) {
			int idx = 0;
            int num=-1;
			while (true)
			{
				idx = (int)str.find(strFrom, idx);
				if (idx >= 0) {
                    num++;
                    if (idxCount<=0 || (num>=idxStart && num<idxStart+idxCount)) {
                        str.replace(idx, flen, strTo);
                    }
					idx += tlen;
				}
				else {
					break;
				}
			}
		}
	}

}